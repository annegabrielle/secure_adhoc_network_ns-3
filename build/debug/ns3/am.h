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

/* In order to include these C function in the C++ code */
#ifdef __cplusplus
extern "C" {
#endif

#ifndef AM_H
#define AM_H

//#include "batman.h"
//#include "os.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <linux/string.h>
#include <stdio.h>
#include <fcntl.h>
#include <time.h>
#include <pthread.h>

#include <openssl/bio.h>
#include <openssl/buffer.h>
#include <openssl/pem.h>
#include <openssl/conf.h>
#include <openssl/x509v3.h>
#include <openssl/evp.h>
#include <openssl/ec.h>
#include <openssl/ecdh.h>
#include <openssl/ecdsa.h>
#include <openssl/hmac.h>
#ifndef OPENSSL_NO_ENGINE
#include <openssl/engine.h>
#endif

#include <openssl/asn1.h>
#include <openssl/asn1t.h>
#include <openssl/asn1_mac.h>

/*
 * TEMP
 */
void tool_dump_memory(unsigned char *data, size_t len);

/* Definitions */
#define IF_NAMESIZE			16
#define AM_PORT 			64305
#define MAXBUFLEN 			1500-20-8 //MTU - IP_HEADER - UDP_HEADER
#define SUBJECT_NAME_SIZE 	16
#define FULL_SUB_NM_SZ		3*SUBJECT_NAME_SIZE
#define AES_BLOCK_SIZE 		16
#define AES_KEY_SIZE 		16
#define AES_IV_SIZE 		16
#define RAND_LEN 			(AES_BLOCK_SIZE*48)-1	//Chosen so auth_packets are well below MAXBUFLEN

#define CRYPTO_DIR			"./.crypto/"
#define MY_KEY				CRYPTO_DIR "my_private_key"
#define MY_CERT				CRYPTO_DIR "my_pc"
#define MY_REQ 				CRYPTO_DIR "my_pc_req"
#define MY_RAND				CRYPTO_DIR "my_rand"
#define MY_SIG				CRYPTO_DIR "my_sig"
#define RECV_REQ			CRYPTO_DIR "recv_pc_req_"
#define RECV_CERT			CRYPTO_DIR "recv_pc_"
#define ISSUED_CERT			CRYPTO_DIR "issued_pc"
#define SP_CERT				CRYPTO_DIR "sp_pc"

#define RSA_KEY_SIZE		1024
//#define ECC_CURVE			NID_sect163k1
#define ECC_CURVE			NID_secp160r1
//#define ECIES_CURVE NID_secp521r1
#define ECDH_CIPHER 		EVP_aes_128_cbc()
#define ECDH_HASHER 		EVP_sha256()


/* Functions */
int openssl_tool_seed_prng(int bytes);void *KDF1_SHA256(const void *in, size_t inlen, void *out, size_t *outlen);

void openssl_key_generate(EVP_CIPHER_CTX *aes_master, int key_count, unsigned char **keyp);
void openssl_tool_gen_rand(unsigned char **rand, int len);

void openssl_key_master_select(unsigned char **key, int b);
void openssl_key_iv_select(unsigned char **iv, int b);

void openssl_key_master_ctx(EVP_CIPHER_CTX *master);
unsigned char *openssl_aes_encrypt(EVP_CIPHER_CTX *e, unsigned char *plaintext, int *len);

int tool_sliding_window(uint16_t seq_num, uint16_t id);

void *KDF1_SHA256(const void *in, size_t inlen, void *out, size_t *outlen);


#endif

#ifdef __cplusplus
}
#endif
