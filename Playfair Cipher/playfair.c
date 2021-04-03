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

	

	/*
	switch(__OPER__(argv[2])) {
		case ENCRYPT:
			output = fopen("encrypted.txt", "w");
			if(output == NULL) {
				perror("Error opening file.");
				exit(0);
			}
			printf("Performing encryption\n");
			perform_encryption();

			break;
		case DECRYPT:
			output = fopen("decrypted.txt", "w");
			if(output == NULL) {
				perror("Error opening file.");
				exit(0);
			}
			printf("Performing decryption\n");
			perform_decryption();

			break;
		default:
			perror("Arrrrgh! No man's land has been reached.\n");
			assert(0); // No man's land.
	}*/

	return 0;
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
}

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