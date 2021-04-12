#include "afine_lib.h"

int main(int argc, char* argv[]) {
	FILE *f_plaintext = fopen(argv[1], "r");
	FILE *output;
	char c,encrypted_c,decrypted_c;
	char *ciphertext;

	if(f_plaintext == NULL) {
		perror("Error opening file.");
	}

	unsigned char *plaintext = read_input(f_plaintext);
	
	switch(__OPER__(argv[2])) {
		case ENCRYPT:
			output = fopen("encrypted.txt", "w");
			if(output == NULL) {
				perror("Error opening file.");
				exit(0);
			}
			printf("Performing encryption\n");
			while(c = *plaintext++) {
				c = toupper(c);
				encrypted_c = affine_encrypt(c);
				strcat(ciphertext, plaintext, &encrypted_c);
			}

			break;
		case DECRYPT:
			output = fopen("decrypted.txt", "w");
			if(output == NULL) {
				perror("Error opening file.");
				exit(0);
			}
			printf("Performing decryption\n");
			while(c = *plaintext++) {
				if(__VALID__(c)) {
					c = toupper(c);
					decrypted_c = affine_decrypt(c);
					*ciphertext++ = decrypted_c;
					strcat(ciphertext, plaintext, &decrypted_c);
				}
			}

			break;
		default:
			perror("Arrrrgh! No man's land has been reached.\n");
			assert(0); // No man's land.
	}

	return 0;
}

uint8_t 
affine_encrypt(char c){
	return ((11 * (int) c) +  19) % 26;
}

uint8_t 
affine_decrypt(char c){
	return ((1/11)*((int) c - 19) % 26
}

int 
find_key(char c) {
    return (int) c - (int) 'A';
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