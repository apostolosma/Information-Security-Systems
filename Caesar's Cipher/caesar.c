#include "caesar_lib.h"

/* 
	*Caesar's Cipher:*

	Each character of the plaintext is replaced by a character found
	at some fixed number of positions down the alphabet/ASCII set.

	For
	example, given the ASCII character set, a shift of 3 will
	replace the letter “A” of the plaintext	with the letter “D” at the 
	ciphertext.
	Also, a shift of 4 will encrypt the plaintext “hello” as “lipps”
*/

int 
main(int argc, char* argv[]) {

	FILE *f_plaintext = fopen(argv[1], "r");
	FILE *output = fopen("result.txt", "a");
	unsigned char *input_text, *ctxt, *plaintext;


	if(f_plaintext == NULL) {
		perror("Error opening file.");
	}

	__init__(f_plaintext);

	input_text = NULL;
	input_text = read_input(f_plaintext);

	output = fopen("result.txt","a");
	if(output == NULL) {
		perror("Error opening file.");
		exit(0);
	}

	printf("Performing encryption.\n");
	ctxt = perform_encryption_caesar(input_text);
	printf("Performing decryption.\n");
	plaintext = perform_decryption_caesar(ctxt);

	for(int i = 0; i < strlen(ctxt);i++) {
		fprintf(output,"%c",ctxt[i]);
	}
	fprintf(output,"\n");
	for(int i = 0; i < strlen(plaintext);i++) {
		fprintf(output,"%c",plaintext[i]);
	}
	fprintf(output,"\n");
	return 0;
}

unsigned char
caesar_encrypt(unsigned char c, int shift) {
	uint8_t index, i = 0;
	unsigned short encrypted_c;

	while( i < ALP_SIZE) {
		if(c == vocabulary[i]) {
			index = i;
			break;
		}

		i++;
	}

	if(index + shift >= ALP_SIZE) {
		encrypted_c = (index + shift) % ALP_SIZE;
	} else {
		encrypted_c = index + shift;
	}

	return vocabulary[encrypted_c];

}

unsigned char
caesar_decrypt(unsigned char c, int shift) {
	uint8_t index, i = 0;
	unsigned short decrypted_c;

	while( i < ALP_SIZE) {
		if(c == (int) vocabulary[i]) {
			index = i;
			break;
		}

		i++;
	}

	if(index - shift < 0) {
		decrypted_c = ALP_SIZE + (index - shift); /* (index - shift) is a negative number, so adding it to ALP_SIZE is like subtraction  */
	} else {
		decrypted_c = index - shift;
	}

	return vocabulary[decrypted_c];
}

void 
__init__(FILE *f_plaintext) {
	int i,tokens_inserted = 0;

	for(i = ASCII_NUM_START; i <= ASCII_NUM_END; i++) {

		vocabulary[tokens_inserted] = (char) i;

		tokens_inserted++;
	}

	for(i = ASCII_BL_START; i <= ASCII_BL_END; i++) {

		vocabulary[tokens_inserted] = (char) i;

		tokens_inserted++;
	} 

	for(i = ASCII_SL_START; i <= ASCII_SL_END; i++) {

		vocabulary[tokens_inserted] = (char) i;

		tokens_inserted++;
	} 

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

unsigned char * 
perform_encryption_caesar(unsigned char *input_text) {
	unsigned char c,encrypted_c;
	unsigned char *ctxt = NULL;
	int counter = 0;


	for(int i = 0; i < strlen(input_text); i++) {
		if (__VALID__(input_text[i]) && !__ES_CH__(input_text[i]))
		{
			encrypted_c = caesar_encrypt(input_text[i], N);
			
			ctxt = append_char(ctxt, encrypted_c);
		} else if (!__ES_CH__(input_text[i])){
			/* If char is an escape character or a space, just ignore it.*/
			fprintf(stderr,"UNRECOGNISED CHARACTER (%c): File stream contains unrecognised character.\nThis algorithm supports Numbers[0-9] and Letters[A-Za-z].\n", input_text[i]);
			exit(0);
		}
	}

	return ctxt;
}

unsigned char * 
perform_decryption_caesar(unsigned char *input_text){
	char c,decrypted_c;
	unsigned char *plaintext = NULL;

	for(int i = 0; i < strlen(input_text); i++) {
		if (__VALID__(input_text[i]))
		{
			decrypted_c = (char) caesar_decrypt(input_text[i], N);
			plaintext = append_char(plaintext, decrypted_c);

		} else if (!__ES_CH__(input_text[i])){
			/* If char is an escape character or a space, just ignore it.*/
			fprintf(stderr,"UNRECOGNISED CHARACTER %c: File stream contains unrecognised character.\nThis algorithm supports Numbers[0-9] and Letters[A-Za-z].\n", c);
			exit(0);
		}
	}

	return plaintext;
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
	

	return plaintext;
}