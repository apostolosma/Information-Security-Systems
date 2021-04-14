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
	FILE *output = fopen("result.txt", "a");
	unsigned char *e,*d;

	if(f_plaintext == NULL) {
		perror("Error opening file.");
	}

	unsigned char *plaintext = read_input(f_plaintext);

	__init__(seen);

	construct_grid(plaintext);

	e = playfair_encrypt(plaintext);
	d = playfair_decrypt(e);

	fprintf(output, "\tENCRYPTION:\n%s\n\n", e);
	fprintf(output, "\tDECRYPTION:\n%s\n\n", d);
	fclose(output);

	return 0;
}

unsigned char * 
playfair_encrypt(unsigned char *plaintext){
	char c1, c2, encrypted_c1, encrypted_c2; // characters to be encrypted
	Pair *pc1, *pc2;
	unsigned char *ciphertext = NULL;

	pc1 = (Pair *) malloc(sizeof(Pair) * 1);
	pc2 = (Pair *) malloc(sizeof(Pair) * 1);

	unsigned int size = strlen(plaintext);

	if(size % 2 == 1) {
		char x = 'x';
		strncat(plaintext, &x, 1);
	}

	printf("size: %d\n",size);
	
	while(1) {
		if(size <= 0) {
			break;
		}

		c1 = *plaintext++;
		c2 = *plaintext++;

		printf("c1:%c\t&c2:%c -> ",c1,c2);
		if(c1 == 'J') c1 = 'I';
		if(c2 == 'J') c2 = 'I';
		
		if( c1 == c2 ) {
			encrypted_c1 = c1;
			encrypted_c2 = 'X';
		}
		else{
			check_position(c1,pc1);
			check_position(c2,pc2);
			if(pc1 -> row == pc2 -> row) {

				if(wrap(pc1 -> col)) {
					pc1 -> col = 0;
					if(pc1 -> row != 4)
					{
						pc1 -> row ++;
					} else {
						pc1 -> row = 0;
					}
				}
				else {
					pc1 -> col++;
				}
				if(wrap(pc2 -> col)) {
					pc2 -> col = 0;
					if(pc2 -> row != 4)
					{
						pc2 -> row ++;
					} else {
						pc2 -> row = 0;
					}
				}
				else {
					pc2 -> col ++;
				}
				encrypted_c1 = grid[pc1 -> row][pc1 -> col];
				encrypted_c2 = grid[pc2 -> row][pc2 -> col];
				
			}
			else if(pc1 -> col == pc2 -> col) {
				if(wrap(pc1 -> row)) {
					pc1 -> row = 0;
					if(pc1 -> col != 4) {
						pc1 -> col ++;
					} else {
						pc1 -> col = 0;
					}
				}
				if(wrap(pc2 -> row)) {
					pc2 -> row = 0;
					if(pc2 -> col != 4) {
						pc2 -> col ++;
					} else {
						pc2 -> col = 0;
					}
				}
				encrypted_c1 = grid[pc1 -> row][pc1 -> col];
				encrypted_c2 = grid[pc2 -> row][pc2 -> col];
			}
			else if(pc1 -> row != pc2 -> row && pc1 -> col != pc2 -> col) {
				encrypted_c1 = grid[pc1 -> row][pc2 -> col];
				encrypted_c2 = grid[pc2 -> row][pc1 -> col];
			}
		}
		size = size - 2;

		printf("en_c1:%c\t&en_c2:%c\n",encrypted_c1,encrypted_c2);
		ciphertext = append_string(ciphertext, encrypted_c1, encrypted_c2);
		printf("%s\n",ciphertext);
	}

	return ciphertext;

}

unsigned char *
playfair_decrypt(unsigned char *plaintext){
	char c1, c2, encrypted_c1, encrypted_c2; // characters to be encrypted
	Pair *pc1, *pc2;
	unsigned char *ciphertext = NULL;
	
	pc1 = (Pair *) malloc(sizeof(Pair) * 1);
	pc2 = (Pair *) malloc(sizeof(Pair) * 1);

	unsigned int size = strlen(plaintext);

	if(size % 2 == 1) {
		char x = 'x';
		strncat(plaintext, &x, 1);
	}

	while(1) {
		if(size <= 0) {
			break;
		}
		c1 = *plaintext++;
		c2 = *plaintext++;

		if( c2 == 'X' ) {
			encrypted_c1 = c1;
			encrypted_c2 = c1;
		}
		else{
			check_position(c1,pc1);
			check_position(c2,pc2);

			if(pc1 -> row == pc2 -> row) {

				if(reverse_wrap(pc1 -> col)) {
					pc1 -> col = 4;
					if(pc1 -> row != 0) pc1 -> row --;
					else pc1 -> row = 4;
				}
				else {
					pc1 -> col --;
				}

				if(reverse_wrap(pc2 -> col)) {
					pc2 -> col = 4;
					if(pc2 -> row != 0) pc2 -> row --;
					else pc2 -> row = 4;
				}
				else {
					pc2 -> col --;
				}

				encrypted_c1 = grid[pc1 -> row][pc1 -> col];
				encrypted_c2 = grid[pc2 -> row][pc2 -> col];
			}
			if(pc1 -> col == pc2 -> col) {
				if(reverse_wrap(pc1 -> col)) {
					if(pc1 -> col == 0) pc1 -> col = 4;
					else pc1 -> col--;
					pc1->row = 4;
				}
				else {
					pc1 -> row = 4;
				}

				if(reverse_wrap(pc2 -> col)) {
					
					if(pc2 -> col == 0) pc2 -> col = 4;
					else pc2 -> col --;
					pc2 -> row = 4;
				}
				else {
					pc2 -> row = 4;
				}
				encrypted_c1 = grid[pc1 -> row][pc1 -> col];
				encrypted_c2 = grid[pc2 -> row][pc2 -> col];
			}
			if(pc1 -> row != pc2 -> row && pc1 -> col != pc2 -> col) {
				encrypted_c1 = grid[pc1 -> row][pc2 -> col];
				encrypted_c2 = grid[pc2 -> row][pc1 -> col];
			}
		}
		size = size - 2;
		ciphertext = append_string(ciphertext, encrypted_c1, encrypted_c2);
		
	}

	return ciphertext;
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
				if(wrap(col)) {
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
		int counter = 0;
		/* This means our grid has empty cells, so we need to fill them in */
		for(int i = 0; i < 26; i ++) {
			if(!seen[i]) {
				if(wrap(col)) {
					grid[row][col] = (char) (i + 'A');

					row++; col = 0;
				}
				else {
					grid[row][col] = (char) (i + 'A');
					col++;
				}
			}
		}
	}
}


int find_key(char c) {
    return (int) c - (int) 'A';
}

bool wrap(int a) {
    if(a == 4) {
        return true;
    }

     return false;
}

bool reverse_wrap(int a) {
	if(a == 0) return true;

	return false;
}

unsigned char *
read_input(FILE *f_plaintext) {
	unsigned char *plaintext = NULL;
	char c;

	do{
		c = fgetc(f_plaintext);
		
		if(__VALID__(c) && !__ES_CH__(c)) {
			plaintext = append_char(plaintext, c);
		}
	}while(c != EOF);
	
	printf("plaintext: %s", plaintext);

	return plaintext;
}

unsigned char * 
append_string(char *string, char c1, char c2) {
	unsigned char *new;
	if(string != NULL) {
		size_t len = strlen(string) + 3; // 3 comes from '\0' character and size of the characters we want to append.
		new = (unsigned char *)malloc(sizeof(unsigned char *) * len);

		strncat(new, string, strlen(string));
		strncat(new, &c1, 1);
		strncat(new, &c2, 1);
	} else {
		size_t len = 3;
		new = (unsigned char *)malloc(sizeof(unsigned char *) * len);

		strncat(new, &c1, 1);
		strncat(new, &c2, 1);
	}

	return new;
}

unsigned char * 
append_char(char *string, char c1) {
	unsigned char *new;
	if(string != NULL) {
		size_t len = strlen(string) + 2; // 3 comes from '\0' character and size of the characters we want to append.
		new = (unsigned char *)malloc(sizeof(unsigned char *) * len);

		strncat(new, string, strlen(string));
		strncat(new, &c1, 1);
	} else {
		size_t len = 2;
		new = (unsigned char *)malloc(sizeof(unsigned char *) * len);

		strncat(new, &c1, 1);
	}

	return new;
}


void
check_position(char a, Pair *p) {
	for(int i = 0; i < 5; i++) {
		for(int j = 0; j < 5; j++) {
			if(a == grid[i][j]) {
				p -> row = i;
				p -> col = j;
				return;
			}
		}
	}
}