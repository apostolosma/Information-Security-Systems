#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define __ES_CH__(c) (((c == '\n') || (c == '\a') || (c == '\b') || (c == '\v') || (c == '\r') || (c == '\t') || (c == '\'') || (c == '\?') || (c == '\\') || (c == '\"') || (c == '\f') || (c == ' ') || (c == EOF)) ? 1 : 0)
#define	__VALID__(c)		( (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ? 1 : 0)

FILE *output;
char *algorithm;
int rounds;
unsigned char subkeys[8][4];

unsigned char *round_function(unsigned char *block, unsigned char *subkey);

unsigned char *feistel_encrypt(unsigned char *block, short N);

unsigned char *feistel_decrypt(unsigned char *block, short N);

unsigned char *append_char(unsigned char *string, char c);

void read_input(FILE *f_plaintext);

FILE *handle_configs(FILE *configs, FILE *plaintext);

void generate_key(unsigned char *buffer);

void hash_function(unsigned char *buffer, unsigned char *right, unsigned char *subkey);
