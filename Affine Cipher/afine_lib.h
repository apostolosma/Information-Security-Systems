#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define __ES_CH__(c) (((c == '\n') || (c == '\a') || (c == '\b') || (c == '\v') || (c == '\r') || (c == '\t') || (c == '\'') || (c == '\?') || (c == '\\') || (c == '\"') || (c == '\f') || (c == ' ') || (c == EOF)) ? 1 : 0)
#define	__VALID__(c)		( (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ? 1 : 0)

char affine_encrypt(char c);

char affine_decrypt(char c);

int find_key(char c);

unsigned char *read_input(FILE *f_plaintext);

char *append_char(char *string, char c);

unsigned char *read_input(FILE *f_plaintext);