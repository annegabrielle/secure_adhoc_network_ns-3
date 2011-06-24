/*
 *
 * Authentication Module
 *
 * Used for creating a authentication channel, and other authentication purposes
 *
 * Created on : 1. feb. 2011
 * Author     : Espen Graarud
 * Email      : espengra@stud.ntnu.no
 * Project    : Implementing a Secure Ad Hoc Network
 * Institution: NTNU (Norwegian University of Science & Technology), ITEM (Institute of Telematics)
 *
 */

#include "am.h"


void *KDF1_SHA256(const void *in, size_t inlen, void *out, size_t *outlen) {

    if (*outlen < SHA256_DIGEST_LENGTH) {
    	return NULL;
    }
    else {
        *outlen = SHA256_DIGEST_LENGTH;
    }
    return SHA256(in, inlen, out);
}

/* Debugging purposes */
void tool_dump_memory(unsigned char* data, size_t len) {
	size_t i;
	printf("Data in [%p..%p): ",data,data+len);
	for (i=0;i<len;i++) {
		if(!(i%32)) {
			printf("\n[%4d - %4d]: ",i, ( i+32 <= len ? i+32 : len ));
		}
		printf("%02X ", ((unsigned char*)data)[i]);
	}
	printf("\n");
}

/* Usage function for my AM extension */
void secure_usage() {
	fprintf( stderr, "Secure Usage: batman [options] -R/--role 'sp/authenticated/restricted' interface [interface interface]\n" );
	fprintf( stderr, "       -R / --role 'sp'              start as Service Proxy / Master node\n" );
	fprintf( stderr, "       -R / --role 'authenticated'   request to become authenticated with full rights\n" );
	fprintf( stderr, "       -R / --role 'restricted'      request to become restricted (end-node only)\n" );
}



//keep
/* Create RAND for Routing Auth Data */
void openssl_tool_gen_rand(unsigned char **rv, int len) {
	if(*rv == NULL || rv == NULL) {
		*rv = malloc(len);
	}
	RAND_pseudo_bytes(*rv,len);
}


/* Seeding the PRNG */
int openssl_tool_seed_prng(int bytes) {
	if(!RAND_load_file("/dev/urandom", bytes))
		return 0;
	return 1;
}

/* Create AES Keys and contexts */
//keep
/* Generate Context for Encryption with Master Key */
void openssl_key_master_ctx(EVP_CIPHER_CTX *master) {

	unsigned char *aes_master_key = NULL;
	unsigned char *aes_master_iv = NULL;

	openssl_key_master_select(&aes_master_key, AES_KEY_SIZE);
	openssl_key_iv_select(&aes_master_iv, AES_IV_SIZE);

	EVP_EncryptInit(master, EVP_aes_128_cbc(), aes_master_key, aes_master_iv);

	free(aes_master_iv);
	free(aes_master_key);
}
//keep
/* Random key for input to the AES key generation, i.e. insted of user password */
void openssl_key_master_select(unsigned char **k, int b) {
//	int i;
	unsigned char *key;

	if(*k == NULL || k == NULL) {
		key = malloc(b);

	} else {
		key = *k;
	}

	if(!RAND_bytes(key, b)) {
		printf("Master Key Generation Failed!\n");
		exit(0);
	}

	*k = key;

}
//keep
void openssl_key_iv_select(unsigned char **i, int b) {

	unsigned char *iv;

	if(*i == NULL || i == NULL) {
		iv = malloc(AES_IV_SIZE);
	} else {
		iv = *i;
	}

	if(!RAND_pseudo_bytes(iv,b)){
		printf("IV Generation Failed\n");
		exit(0);
	}

	*i = iv;
}

//keep
/*
 * Encrypt *len bytes of data
 * All data going in & out is considered binary (unsigned char[])
 */
unsigned char *openssl_aes_encrypt(EVP_CIPHER_CTX *e, unsigned char *plaintext, int *len)
{
//  printf("openssl_printf\n");
  /* max ciphertext len for a n bytes of plaintext is n + AES_BLOCK_SIZE -1 bytes */
  int c_len = *len + AES_BLOCK_SIZE, f_len = 0;
  unsigned char *ciphertext = malloc(c_len);

  /* allows reusing of 'e' for multiple encryption cycles */
//  EVP_EncryptInit_ex(e, NULL, NULL, NULL, NULL);

  /* update ciphertext, c_len is filled with the length of ciphertext generated,
    *len is the size of plaintext in bytes */
  EVP_EncryptUpdate(e, ciphertext, &c_len, plaintext, *len);

  /* update ciphertext with the final remaining bytes */
  EVP_EncryptFinal(e, ciphertext+c_len, &f_len);

  *len = c_len + f_len;
  return ciphertext;
}

//keep
/* Generate new key (incl. IV), from master key */
void openssl_key_generate(EVP_CIPHER_CTX *aes_master, int key_count, unsigned char **keyp) {

	unsigned char *ret;
//	int i;
	int tmp, ol;

	if(keyp == NULL || *keyp == NULL) {
		ret = malloc(EVP_CIPHER_CTX_block_size(aes_master));
	} else {
		memset(*keyp, 0, EVP_CIPHER_CTX_block_size(aes_master));
		ret = *keyp;
	}

	ol = 0;

	/* Create plaintext from key_count - each new key will be cipher of i=1,2,3... */
	unsigned char *plaintext = malloc(sizeof(key_count));
	memset(plaintext, 0, sizeof(plaintext));
	*plaintext = (unsigned char)key_count;
	int len = strlen((char *)plaintext)+1;

	EVP_EncryptUpdate(aes_master, ret, &tmp, plaintext, len);
	ol += tmp;
//	EVP_EncryptFinal(aes_master, ret+ol, &tmp);
	//Remove padding, not wanted for key!
	EVP_EncryptFinal(aes_master, ret, &tmp);

//	printf("Generated New Current Key #%d: ",key_count);
//
//	for(i=0;i<tmp-1;i++) {
//		printf("%02X:",ret[i]);
//	}
//	printf("%02X\n", ret[tmp-1]);

	free(plaintext);
	*keyp = ret;

}


/* Manage sliding window to prevent replay attacks */
int tool_sliding_window(uint16_t seq_num, uint16_t id) {
//
//	int i;
//	for (i=0; i<100; i++) {
//
//		/* Find the node id in neighbor list */
//		if(id == neigh_list[i]->id) {
//
//			/* Received Auth Sequence Number is newer/higher than last */
//			if (seq_num > neigh_list[i]->last_seq_num) {
//
//				/* Shift window according to the difference between new and last seq num */
//				int difference = seq_num - neigh_list[i]->last_seq_num;
//				neigh_list[i]->window = neigh_list[i]->window << difference;
//
//				/* Set bit in window to indicate this seq num received */
//				neigh_list[i]->window = neigh_list[i]->window | 1;
//
//				/* Update new last seq num to new one */
//				neigh_list[i]->last_seq_num = seq_num;
//
//				return 1;
//
//			}
//
//			/* Received Auth Sequence Number is inside the window size */
//			else if (seq_num >= neigh_list[i]->last_seq_num - 63) {		//window size 64
//
//				int offset = ( neigh_list[i]->last_seq_num - seq_num ) % 64;
//
//				/* Check whether the packet is received before, i.e. the bit is set */
//				if(neigh_list[i]->window & ( 1 << offset )) {
//
//					printf("Received replay packet, throwing away!\n\n");
//					return 0;
//				}
//
//				/* If not, then add to window */
//				else {
//
//					/* Set bit in window to indicate this seq num received */
//					neigh_list[i]->window = neigh_list[i]->window | ( 1 << offset );
//
//					return 1;
//				}
//
//			}
//
//			/* Received Auth Sequence Number is outside window size, old */
//			else {
//
//				printf("Received old (possible replay) packet, throwing away!\n");
//				return 0;
//			}
//		}
//	}

	/* Should not get here  if function called correctly! */
	return 0;

}
