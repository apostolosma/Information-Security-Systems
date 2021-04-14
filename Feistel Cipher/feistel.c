#include "feistel_lib.h"

int main(int argc, char* argv[]) {
	FILE *f_plaintext;
	FILE *configs = fopen("config.txt", "r");
	char c,encrypted_c,decrypted_c;
	unsigned char *ciphertext;

	/*if(f_plaintext == NULL) {
		perror("Error opening file.");
	}*/

	if(configs == NULL) {
		perror("Error opening file.");
	}


	f_plaintext = handle_configs(configs,f_plaintext);

	if(f_plaintext == NULL) {
		printf("Error opening file.\n");
	}

	read_input(f_plaintext);
	/*unsigned char *plaintext = read_input(f_plaintext);
	
	output = fopen("result.txt", "a");
	if(output == NULL) {
		perror("Error opening file.");
		exit(0);
	}

	ciphertext = feistel_encrypt(plaintext);
	fprintf(output, "%s", ciphertext);

	plaintext = "";
	plaintext = feistel_decrypt(ciphertext);

	fprintf(output, "%s", plaintext);
	*/
	return 0;
}

unsigned char *
round_function(unsigned char *block, unsigned char *subkey) {
	assert(block);
	assert(subkey);

	unsigned char *left, *right, *temp;

	printf("\n\t-Splitting block\n");
	left = (unsigned char *) malloc(sizeof(char ) * 4);
	temp = (unsigned char *) malloc(sizeof(char ) * 4);
	right = (unsigned char *) malloc(sizeof(char ) * 4);

	for(int i = 0; i < 4; i++) {
		left[i] = block[i];
		right[i] = block[4 + i];
	}

	printf("\t-LEFT:%s\n", left);
	printf("\t-RIGHT:%s\n", right);
	
	hash_function(temp, right, subkey);

	for(int i = 0; i < 4; i++) {
		block[i+4] = left[i] ^ temp[i];
		block[i] = right[i];
	}

	return block;
}

void
generate_key(unsigned char *buffer) {
	int fd = open("/dev/urandom", O_RDONLY);
    read(fd, buffer, 4);
	close(fd);
}

void 
hash_function(unsigned char *buffer, unsigned char *right, unsigned char *subkey) {

	for(int i = 0; i < 4 ; i++) {
		buffer[i] = (right[i] * subkey[i]) % (2^32); 
	}
}

unsigned char *
feistel_encrypt(unsigned char *block, short N) {
	if (N == rounds) {
		unsigned char *left = (unsigned char *) malloc(sizeof(char ) * 4);
		unsigned char *right = (unsigned char *) malloc(sizeof(char ) * 4);

		for(int i = 0; i < 4; i++) {
			left[i] = block[i];
			right[i] = block[4 + i];
		}

		for(int i = 0; i < 4; i++) {
			block[i] 	= right[i];
			block[i+4] 	= left[i];
		}
		printf("---------------------------------------------\n");
		return block;
	} 

	unsigned char *subkey = (unsigned char *)malloc(sizeof(char) * 4);

	generate_key(subkey);

	//store subkey into memory
	strcpy(subkeys[N],subkey);

	printf("SUBKEY(%d): ", N);
	for(int i = 0; i < 4; i++)
        printf("%02X ", subkey[i]);
    printf("\n");

	printf("Calling round function\n");
	block = round_function(block, subkey);
	printf("RESULT: %s -> ", block);
	for(int i = 0; i < 8; i++)
        printf("%02X ", block[i]);
    printf("\n");

	feistel_encrypt(block, N+1);

}

unsigned char *
feistel_decrypt(unsigned char *block, short N) {
	if(N == 0) {
		unsigned char *left = (unsigned char *) malloc(sizeof(char ) * 4);
		unsigned char *right = (unsigned char *) malloc(sizeof(char ) * 4);

		for(int i = 0; i < 4; i++) {
			left[i] = block[i];
			right[i] = block[4 + i];
		}

		for(int i = 0; i < 4; i++) {
			block[i] 	= right[i];
			block[i+4] 	= left[i];
		}
		printf("\n\nFINAL RESULT: %s\n", block);
		printf("---------------------------------------------\n");
		return block;
	}

	printf("SUBKEY(%d): ", N - 1);
	for(int i = 0; i < 4; i++)
        printf("%02X ", subkeys[N-1][i]);
    printf("\n");

	printf("Calling round function\n");
	block = round_function(block, subkeys[N-1]);
	printf("RESULT: %s -> ", block);
	for(int i = 0; i < 8; i++)
        printf("%02X ", block[i]);
    printf("\n");

	feistel_decrypt(block, N-1);
}


void
read_input(FILE *f_plaintext) {
	unsigned char *block = NULL;
	char c;
	short counter = 0;

	do{
		c = fgetc(f_plaintext);
		
		if(__VALID__(c) && !__ES_CH__(c)) {
			block = append_char(block, c);
			counter++;
			if(counter % 8 == 0) {
				printf("BLOCK TO ENCRYPT: %s\n", block);
				printf("---------------------------------------------\n");
				block = feistel_encrypt(block, 0);
				printf("BLOCK TO DECRYPT: %s\n", block);
				block = feistel_decrypt(block,rounds);

				exit(0);
				counter = 0;
				block = NULL;
			}
		}
	}while(c != EOF);

	if(counter != 0) {
		//Here we need to apply padding

	}

	return;
}


unsigned char * 
append_char(unsigned char *string, char c1) {
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


FILE *
handle_configs(FILE *configs, FILE *f_plaintext){
	char *line = (char *)malloc(sizeof(char)*100);
	
	while(fscanf(configs,"%s",line) != EOF) {
		if(strcmp(line, "algorithm") == 0) {
			fscanf(configs,"%s",line); //ignore '=' character
			fscanf(configs,"%s",line);
			algorithm = (char *)malloc(sizeof(char) * strlen(line));
			strcpy(algorithm, line);
		} else if(strcmp(line, "rounds") == 0) {
			fscanf(configs,"%s",line);
			fscanf(configs, "%d", &rounds);
		} else if(strcmp(line, "input") == 0) {
			fscanf(configs,"%s",line);
			fscanf(configs,"%s",line);
			f_plaintext = fopen(line, "r");
		} else if(strcmp(line, "caesar_shift") == 0) {
			//fscanf(configs, "%d", N);
		}
	}

	return f_plaintext;
}