#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>
#include <stdbool.h>

#define	__VALID__(c)		( (c >= 'A' && c <= 'Z') ? 1 : 0)
#define __init__(c) ({\
            for(int i = 0; i < 26; i++) {\
                if(i == 9) c[i] = 1; \
                else c[i] = 0;\
            } \
        })

#define __ES_CH__(c) (((c == '\n') || (c == '\a') || (c == '\b') || (c == '\v') || (c == '\r') || (c == '\t') || (c == '\'') || (c == '\?') || (c == '\\') || (c == '\"') || (c == '\f') || (c == ' ') || (c == EOF)) ? true : false)

typedef struct Pair{
    unsigned short row;
    unsigned short col;
} Pair;

unsigned char grid[5][5];

unsigned int seen[26];

unsigned char *playfair_encrypt(FILE *f_plaintext, unsigned char *plaintext);

unsigned char *playfair_decrypt(FILE *f_plaintext, unsigned char *plaintext);

void construct_grid(unsigned char *plaintext);

int find_key(char c);

bool wrap(int row, int col);

unsigned char *read_input(FILE *f_plaintext);

Pair *check_position(char a);