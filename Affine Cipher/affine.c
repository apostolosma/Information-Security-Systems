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
	
	output = fopen("result.txt", "a");
	if(output == NULL) {
		perror("Error opening file.");
		exit(0);
	}

	printf("Performing encryption\n");
	while(c = *plaintext++) {
		if(__VALID__(c) && !__ES_CH__(c)) {
			c = toupper(c);
			encrypted_c = affine_encrypt(c) + 'A';

			printf("%c->%c\n",c,encrypted_c);
			ciphertext = append_char(ciphertext, encrypted_c);
		}
	}

	fprintf(output, "ENCRYPTION:\n%s\n", ciphertext);

	plaintext = "";
	printf("Performing decryption\n");
	while(c = *ciphertext++) {
		if(__VALID__(c) && !__ES_CH__(c)) {
			c = toupper(c);
			decrypted_c = affine_decrypt(c) + 'A';
			printf("%c\n",decrypted_c);
			plaintext = append_char(plaintext, decrypted_c);
		}
	}

	fprintf(output,"DECRYPTION:\n%s\n",plaintext);

	return 0;
}

char
affine_encrypt(char c){
	int x = ((11 * (int) c) +  19) % 26;
	
	return x;
}

char 
affine_decrypt(char c){
	int mul_inv;
	printf("%c (%d) -> ", c, (int) c);
	for( int i = 0; i < 26; i++) {
		int flag = (11 * i) % 26;

		if(flag == 1) {
			mul_inv = i;
			break;
		}
	}

	int x = mul_inv*((int) c - 19) % 26;
	return x;
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

char *
append_char(char *string, char c){
	char *new;
	if(string == NULL) {
		new = (char *) malloc(sizeof(char)*1);
		strncat(new, &c, 1);
	} else {
		new = (char *) malloc(sizeof(char)*strlen(string));

		strncat(new, string, strlen(string));
		strncat(new, &c, 1);
	}

	return new;

}