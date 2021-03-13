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

	__init__();

	if(plaintext == NULL || cyphertext == NULL) {
		perror("Error opening file.");
	}

	operation = argv[2];

	switch(operation) {
		case "encrypt":
			perform_encryption();
			
			break;
		case "decrypt":
			perforn_decryption();

			break;
		default:
			perror("Arrrrgh! No man's land has been reached.\n");
			assert(0); /* No man's land. */
			exit(0);
	}

	return 0;
}


uint8_t
caesar_encrypt(uint8_t c, unsigned short shift) {
	uint8_t index, i = 0, encrypted_c;

	while( i < ALP_SIZE) {
		if(c == (int) vocabulary[i]) {
			index = i;
			break;
		}

		i++;
	}

	if(index + shift > ALP_SIZE) {
		encrypted_c = (index + shift) mod ALP_SIZE;
	} else {
		encrypted_c = index + shift;
	}

	return vocabulary[encrypted_c];

}

uint8_t
caesar_decrypt(uint8_t c, unsigned short shift) {
	uint8_t index, i = 0, decrypted_c;

	while( i < ALP_SIZE) {
		if(c == (int) vocabulary[i]) {
			index = i;
			break;
		}

		i++;
	}

	if(index - shift < 0) {
		decrypted_c = ALP_SIZE + (index - shift) /* (index - shift) is a negative number, so adding it to ALP_SIZE is like subtraction  */
	} else {
		decrypted_c = index - shift;
	}

	return vocabulary[decrypted_c];
}

void 
__init__() {
	int i, tokens_inserted = 0;

	plaintext = fopen(argv[1], "r");
	cyphertext = fopen(__CYPHER__, "w");

	fread(&N, sizeof(unsigned short), 1, plaintext) /* Reading secret key */

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

char * 
appendString(char *string, char char_to_append){
	char *temp;

	temp = (char *) malloc(sizeof(char) * (strlen(string) + 1));

	strcpy(temp, string);
	strcpy(temp, char_to_append);

	free(string);
	return &temp;
}

void 
perform_encryption() {
	char c,encrypted_c;

	do {
		c = fgetc(plaintext);
		if (__VALID__(c))
		{
			encrypted_c = (char) encrypt(c, N);

			ctxt = appendString(ctxt, encrypted_c);

		} else {
			perror("UNRECOGNISED CHARACTER: File stream contains unrecognised character.\n
					This algorithm supports Numbers[0-9] and Letters[A-Za-z].\n");
		}

	} while(c != EOF)

	fclose(plaintext);
	fclose(cyphertext);
}

void 
perform_decryption(){
	char c,decrypted_c;

	do {
		c = fgetc(plaintext);
		if (__VALID__(c))
		{
			decrypted_c = (char) decrypt(c, N);

			ctxt = appendString(ctxt, decrypted_c);

		} else {
			perror("UNRECOGNISED CHARACTER: File stream contains unrecognised character.\n
					This algorithm supports Numbers[0-9] and Letters[A-Za-z].\n");
		}

	} while(c != EOF)

	fclose(plaintext);
	fclose(cyphertext);
}