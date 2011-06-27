/*
 *
 * BATMAN Bit Array/Sliding Window insipred by the bitarray class in the real BATMAN implementation
 *
 * Author     : Anne Gabrielle Bowitz
 * Email      : bowitz@stud.ntnu.no
 * Project    : Simulation of a Secure Ad Hoc Network Routing protocol
 * Institution: NTNU (Norwegian University of Science & Technology), ITEM (Institute of Telematics)
 *
 */


#include "batman-routing-protocol.h"
#define TYPE_OF_WORD uintmax_t /* you should choose something big, if you don't want to waste cpu */
#define WORD_BIT_SIZE ( sizeof(TYPE_OF_WORD) * 8 )


void bit_init( TYPE_OF_WORD *seq_bits );
uint8_t get_bit_status( TYPE_OF_WORD *seq_bits, uint16_t last_seqno, uint16_t curr_seqno );
char *bit_print( TYPE_OF_WORD *seq_bits );
void bit_mark( TYPE_OF_WORD *seq_bits, int32_t n );
void bit_shift( TYPE_OF_WORD *seq_bits, int32_t n );
char bit_get_packet( TYPE_OF_WORD *seq_bits, int16_t seq_num_diff, int8_t set_mark );
int  bit_packet_count( TYPE_OF_WORD *seq_bits );
uint8_t bit_count( int32_t to_count );

