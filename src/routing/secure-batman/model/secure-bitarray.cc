/*
 * Copyright (C) 2006-2009 B.A.T.M.A.N. contributors:
 *
 * Simon Wunderlich, Axel Neumann, Marek Lindner
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of version 2 of the GNU General Public
 * License as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA
 *
 */



#include <stdio.h>              /* printf() */
#include "ns3/log.h"
#include "secure-bitarray.h"
//#include "os.h"

#define TYPE_OF_WORD uintmax_t /* you should choose something big, if you don't want to waste cpu */
uint8_t sec_num_words = (TQ_LOCAL_WINDOW_SIZE / WORD_BIT_SIZE);
uint8_t sec_local_win_size = TQ_LOCAL_WINDOW_SIZE;

NS_LOG_COMPONENT_DEFINE ("SecureBitarray");

/* clear the bits */
void sec_bit_init( TYPE_OF_WORD *seq_bits ) {

	int i;

	for (i = 0 ; i < (int)sec_num_words; i++)
		seq_bits[i]= 0;

}

/* returns true if corresponding bit in given seq_bits indicates so and curr_seqno is within range of last_seqno */
uint8_t sec_get_bit_status( TYPE_OF_WORD *seq_bits, uint16_t last_seqno, uint16_t curr_seqno ) {

	int16_t diff, word_offset, word_num;

	diff= last_seqno- curr_seqno;
	if (diff < 0 || diff >= sec_local_win_size) { // agb: curr_seq is outside of range
		return 0;

	} else {

		word_offset= ( last_seqno - curr_seqno ) % WORD_BIT_SIZE;	/* which position in the selected word */
		word_num   = ( last_seqno - curr_seqno ) / WORD_BIT_SIZE;	/* which word */

		if ( seq_bits[word_num] & 1<<word_offset )   /* get position status */ //agb: & bitwise AND
			return 1;
		else
			return 0;

	}

}

/* turn corresponding bit on, so we can remember that we got the packet */
void sec_bit_mark( TYPE_OF_WORD *seq_bits, int32_t n ) {
	int32_t word_offset,word_num;

	if (n<0 || n >= sec_local_win_size) {			/* if too old, just drop it */
/* 		printf("got old packet, dropping\n");*/
		return;
	}

/* 	printf("mark bit %d\n", n); */

	word_offset= n%WORD_BIT_SIZE;	/* which position in the selected word */
	word_num   = n/WORD_BIT_SIZE;	/* which word */
//	NS_LOG_DEBUG("word_offset: " << word_offset << " word_num: " << word_num);
	seq_bits[word_num]|= 1<<word_offset;	/* turn the position on */

}

/* shift the packet array p by n places. */
void sec_bit_shift( TYPE_OF_WORD *seq_bits, int32_t n ) {
	int32_t word_offset, word_num;
	int32_t i;

/*	bit_print( seq_bits );*/
	if( n<=0 ) return;

	word_offset= n%WORD_BIT_SIZE;	/* shift how much inside each word */
	word_num   = n/WORD_BIT_SIZE;	/* shift over how much (full) words */

	for ( i=sec_num_words-1; i>word_num; i-- ) {
		/* going from old to new, so we can't overwrite the data we copy from. *
 		 * left is high, right is low: FEDC BA98 7654 3210
		 *	                                  ^^ ^^
		 *                             vvvv
		 * ^^^^ = from, vvvvv =to, we'd have word_num==1 and
		 * word_offset==WORD_BIT_SIZE/2 ????? in this example. (=24 bits)
		 *
		 * our desired output would be: 9876 5432 1000 0000
		 * */

		seq_bits[i]=
			(seq_bits[i - word_num] << word_offset) +
					/* take the lower port from the left half, shift it left to its final position */
			(seq_bits[i - word_num - 1] >>	(WORD_BIT_SIZE-word_offset));
					/* and the upper part of the right half and shift it left to it's position */
		/* for our example that would be: word[0] = 9800 + 0076 = 9876 */
	}
	/* now for our last word, i==word_num, we only have the it's "left" half. that's the 1000 word in
	 * our example.*/

	seq_bits[i]= (seq_bits[i - word_num] << word_offset);

	/* pad the rest with 0, if there is anything */
	i--;

	for (; i>=0; i--) {
		seq_bits[i]= 0;
	}
/*	bit_print( seq_bits ); */
}


/* receive and process one packet, returns 1 if received seq_num is considered new, 0 if old  */
char sec_bit_get_packet( TYPE_OF_WORD *seq_bits, int16_t seq_num_diff, int8_t set_mark ) {

	int i;

	/* we already got a sequence number higher than this one, so we just mark it. this should wrap around the integer just fine */
	if ((seq_num_diff < 0) && (seq_num_diff >= -sec_local_win_size)) {

		if ( set_mark )
			sec_bit_mark( seq_bits, -seq_num_diff );

		return 0;

	}

	if ((seq_num_diff > sec_local_win_size) || (seq_num_diff < -sec_local_win_size)) {        /* it seems we missed a lot of packets or the other host restarted */

		if (seq_num_diff > sec_local_win_size)
			NS_LOG_DEBUG("It seems we missed a lot of packets!" <<  seq_num_diff-1);

		if (-seq_num_diff > sec_local_win_size)
			NS_LOG_DEBUG("Other host probably restarted!");

		for (i=0; i<sec_num_words; i++)
			seq_bits[i]= 0;

		if ( set_mark )
			seq_bits[0] = 1;  /* we only have the latest packet */

	} else {

		sec_bit_shift(seq_bits, seq_num_diff);

		if ( set_mark )
			sec_bit_mark(seq_bits, 0);

	}

	return 1;

}

/* count the hamming weight, how many good packets did we receive? just count the 1's ... */
int sec_bit_packet_count( TYPE_OF_WORD *seq_bits ) {

	int i, hamming = 0;
	TYPE_OF_WORD word;

	for (i=0; i<sec_num_words; i++) {

		word = seq_bits[i];
//		NS_LOG_DEBUG("word: " << word << " i: " << WORD_BIT_SIZE << " sec_num_words: " << sec_num_words);
		while (word) {

			word &= word-1;   /* see http://graphics.stanford.edu/~seander/bithacks.html#CountBitsSetKernighan */
			hamming++;
		}
	}

	return(hamming);

}

uint8_t sec_bit_count( int32_t to_count ) {

	uint8_t hamming = 0;

	while ( to_count ) {

		to_count &= to_count-1;   /* see http://graphics.stanford.edu/~seander/bithacks.html#CountBitsSetKernighan */
		hamming++;

	}

	return(hamming);

}
