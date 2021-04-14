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
    short row;
    short col;
} Pair;

unsigned char grid[5][5];

unsigned int seen[26];

unsigned char *playfair_encrypt(unsigned char *plaintext);

unsigned char *playfair_decrypt(unsigned char *plaintext);

void construct_grid(unsigned char *plaintext);

int find_key(char c);

bool wrap(int a);

bool reverse_wrap(int a);

unsigned char *read_input(FILE *f_plaintext);

void check_position(char a,Pair *p);

unsigned char *append_string(char *string, char c1, char c2);

unsigned char *append_char(char *string, char c1);