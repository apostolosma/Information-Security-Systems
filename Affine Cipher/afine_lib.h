#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define __ES_CH__(c) (((c == '\n') || (c == '\a') || (c == '\b') || (c == '\v') || (c == '\r') || (c == '\t') || (c == '\'') || (c == '\?') || (c == '\\') || (c == '\"') || (c == '\f') || (c == ' ') || (c == EOF)) ? true : false)
#define	__VALID__(c)		( (c >= 'A' && c <= 'Z') ? 1 : 0)

uint8_t* affine_encrypt(uint8_t *plaintext);

uint8_t* affine_decrypt(uint8_t *ciphertext);

int find_key(char c);

unsigned char *read_input(FILE *f_plaintext);