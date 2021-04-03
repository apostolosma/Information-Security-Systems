#include "playfair_lib.h"



/*
The Playfair cipher encrypts pairs of letters (digraphs), instead of single letters as is the case
with simpler substitution ciphers such as the Caesar Cipher. The key element of this cipher is a
5x5 grid that represents the key. In order to create the table, the letters of the key are placed in
the grid, from left to right beginning from the first row. Then the rest of the alphabet’s letters are
inserted in the grid alphabetically. Each letter is placed once in the grid. Since the 5x5 grid can
only hold 25 characters J is usually omitted and treated as ‘I’. For example the key grid for the
pass phrase “HELLO WORLD” will create the following key grid
1

*/

int main(int argc, char* argv[]) {
	FILE *f_plaintext = fopen(argv[1], "r");
	FILE *output;

	if(f_plaintext == NULL) {
		perror("Error opening file.");
	}

	unsigned char *plaintext = read_input(f_plaintext);
	
	__init__(seen);

	construct_grid(plaintext);

	
	switch(__OPER__(argv[2])) {
		case ENCRYPT:
			output = fopen("encrypted.txt", "w");
			if(output == NULL) {
				perror("Error opening file.");
				exit(0);
			}
			printf("Performing encryption\n");
			perform_encryption(f_plaintext, plaintext, output);

			break;
		case DECRYPT:
			output = fopen("decrypted.txt", "w");
			if(output == NULL) {
				perror("Error opening file.");
				exit(0);
			}
			printf("Performing decryption\n");
			perform_decryption(f_plaintext, plaintext, output);

			break;
		default:
			perror("Arrrrgh! No man's land has been reached.\n");
			assert(0); // No man's land.
	}

	return 0;
}

unsigned char * 
playfair_encrypt(FILE *f_plaintext, unsigned char *plaintext){
	char c1, c2, encrypted_c1, encrypted_c2; // characters to be encrypted
	Pair *pc1, *pc2;
	char *ciphertext = "";

	if(size % 2 == 1) {
		char x = 'x';
		strncat(plaintext, &x, 1);
	}
	
	unsigned int size = strlen(plaintext);

	while(size >= 0) {
		c1 = *plaintext++;
		c2 = *plaintext++;

		if( c1 == c2 ) {
			encryped_c2 = 'X';
		}
		else{
			pc1 = check_position(c1);
			pc2 = check_position(c2);

			if(pc1 -> row == pc2 -> row) {

				if(wrap(pc1 -> row + 1,pc1 -> col)) {
					pc1 -> row = 0;
					pc2 -> row = 0;
				}

				encrypted_c1 = grid[pc1 -> row + 1][pc1 -> col];
				encrypted_c2 = grid[pc2 -> row + 1][pc2 -> col];
			}
			if(pc1 -> col == pc2 -> col) {
				if(wrap(pc1 -> row, pc1 -> col + 1)) {
					pc1 -> col = 0;
					pc2 -> col = 0;
				}
				encrypted_c1 = grid[pc1 -> row][pc1 -> col + 1];
				encrypted_c2 = grid[pc2 -> row][pc2 -> col + 1];
			}
			if(pc1 -> row != pc2 -> row && pc1 -> col != pc2 -> col) {
				encryped_c1 = grid[pc1 -> row][pc2 -> col];
				encryped_c2 = grid[pc1 -> row][pc2 -> col];
			}
		}
		size--;
		strncat(cyphertext, &encryped_c1, 1);
		strncat(cyphertext, &encryped_c2, 1);
	}

	fprintf(output, "%s", cyphertext);
}

unsigned char *
playfair_decrypt(FILE *f_plaintext, unsigned char *plaintext) {
	
}

void
construct_grid(unsigned char *plaintext) {
	char c,encrypted_c;
	int counter = 0, key;
	int row = 0, col = 0;

	while(c = *plaintext++) {
		if (__VALID__(c))
		{
			key = find_key(c);
			/* This means this is the first time we read this character. */
			/* So we have to import it into our grid. */

			if( !seen[key] ) {
				if(wrap(row,col)) {
					grid[row][col] = c;

					row++; col = 0;
				}
				else {
					grid[row][col] = c;
					
					col++;
				}
				seen[key] = 1; // Updating character in seen array.
			}
		} else if (!__ES_CH__(c)){
			/* If char is an escape character or a space, just ignore it.*/
			fprintf(stderr,"UNRECOGNISED CHARACTER %c: File stream contains unrecognised character.\nThis algorithm supports Numbers[0-9] and Letters[A-Za-z].\n", c);
			exit(0);
		}
	}

	if(row != 4 && col != 4) {
		/* This means our grid has empty cells, so we need to fill them in */
		for(int i = 0; i < 26; i ++) {
			if(!seen[i]) {
				if(wrap(row,col)) {
					grid[row][col] = (char) (i + 'A');

					row++; col = 0;
				}
				else {
					grid[row][col] = c;
					
					col++;
				}
			}
		}
	}
}

void 

int find_key(char c) {
    return (int) c - (int) 'A';
}

bool wrap(int row,int col) {
    if(col == 4) {
        return true;
    }
        return false;
}

unsigned char *
read_input(FILE *f_plaintext) {
	unsigned int size;

	fseek(f_plaintext,0L,SEEK_END);
	size = ftell(f_plaintext);
	rewind(f_plaintext);
	
	unsigned char *dummy = (char *)malloc(sizeof(char) * size);
	unsigned char *plaintext = (char *)malloc(sizeof(char) * size);

	while(fgets(dummy, size, f_plaintext)) {
		strcat(plaintext, dummy);
	}

	return plaintext;
}

Pair *
check_position(char a) {
	Pair p;
	for(int i = 0; i < 5; i++) {
		for(int j = 0; j < 5; j++) {
			if(a == grid[i][j]) {
				p.row = i;
				p.col = j;

				return p;
			}
		}
	}
}