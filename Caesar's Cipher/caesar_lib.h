#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

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
#define __NUMBER__(c)		((c >= ASCII_NUM_START && c <= ASCII_NUM_END) ? TRUE : FALSE)
#define __CAPITAL__(c)		((c >= ASCII_BL_START && c <= ASCII_BL_END) ? TRUE : FALSE)
#define __LETTER__(c)		((c >= ASCII_SL_START && c <= ASCII_SL_END) ? TRUE : FALSE)


char vocabulary[ALP_SIZE];
char *ctxt, *operation;
unsigned short N; /* Denotes how many characters we shift. */

FILE* plaintext, cyphertext;

void __init__();

char * appendString(char *string, char char_to_append);

uint8_t* caesar_encrypt(char *plaintext);

uint8_t* caesar_decrypt(char *ciphertext);

void perform_encryption();

void perform_decryption();