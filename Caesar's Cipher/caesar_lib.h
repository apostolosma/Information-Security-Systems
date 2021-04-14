#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>

#define TRUE				1
#define FALSE				0
#define ALP_SIZE 			62
#define ASCII_NUM_START		48
#define ASCII_NUM_END		57
#define ASCII_BL_START		65
#define ASCII_BL_END		90 
#define ASCII_SL_START		97 
#define ASCII_SL_END		122
#define	__VALID__(c)		((c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') ? 1 : 0)
#define ENCRYPT 			201
#define DECRYPT 			202
#define __OPER__(c) ((strcmp(c, "encryption") == 0 || strcmp(c, "ENCRYPTION") == 0) ? ENCRYPT : ((strcmp(c, "decryption") == 0 || strcmp(c, "DECRYPTION") == 0) ? DECRYPT : FALSE))
#define __ES_CH__(c) (((c == '\n') || (c == '\a') || (c == '\b') || (c == '\v') || (c == '\r') || (c == '\t') || (c == '\'') || (c == '\?') || (c == '\\') || (c == '\"') || (c == '\f') || (c == ' ') || (c == EOF)) ? TRUE : FALSE)


char vocabulary[ALP_SIZE];
int N; /* Denotes how many characters we shift. */


void __init__(FILE *f_plaintext);

unsigned char *append_char(unsigned char *string, char c);

unsigned char caesar_encrypt(unsigned char c, int shift);

unsigned char caesar_decrypt(unsigned char c, int shift);

unsigned char *perform_encryption_caesar(unsigned char *input_text);

unsigned char *perform_decryption_caesar(unsigned char *input_text);

unsigned char *read_input(FILE *f_plaintext);