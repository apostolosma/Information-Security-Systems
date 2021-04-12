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
#define	__VALID__(c)		((c >= ASCII_SL_START && c <= ASCII_SL_END) || (c >= ASCII_NUM_START && c <= ASCII_NUM_END) || (c >= ASCII_BL_START && c <= ASCII_BL_END) ? 1 : 0)
#define ENCRYPT 			201
#define DECRYPT 			202
#define __OPER__(c) ((strcmp(c, "encryption") == 0 || strcmp(c, "ENCRYPTION") == 0) ? ENCRYPT : ((strcmp(c, "decryption") == 0 || strcmp(c, "DECRYPTION") == 0) ? DECRYPT : FALSE))
#define __ES_CH__(c) (((c == '\n') || (c == '\a') || (c == '\b') || (c == '\v') || (c == '\r') || (c == '\t') || (c == '\'') || (c == '\?') || (c == '\\') || (c == '\"') || (c == '\f') || (c == ' ') || (c == EOF)) ? TRUE : FALSE)


char vocabulary[ALP_SIZE];
char *ctxt;
unsigned short N; /* Denotes how many characters we shift. */

FILE* plaintext;
FILE* output;

void __init__();

char * append_string(char *string, char char_to_append);

uint8_t caesar_encrypt(uint8_t c, unsigned short shift);

uint8_t caesar_decrypt(uint8_t c, unsigned short shift);

void perform_encryption();

void perform_decryption();