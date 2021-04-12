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

	plaintext = fopen(argv[1], "r");
	


	if(plaintext == NULL) {
		perror("Error opening file.");
	}

	__init__();


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
			assert(0); /* No man's land. */
			exit(0);
	}

	return 0;
}
uint8_t
caesar_encrypt(uint8_t c, unsigned short shift) {
	uint8_t index, i = 0;
	unsigned short encrypted_c;

	while( i < ALP_SIZE) {
		if(c == (int) vocabulary[i]) {
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

uint8_t
caesar_decrypt(uint8_t c, unsigned short shift) {
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
__init__() {
	int i,t,tokens_inserted = 0;

	fscanf(plaintext, "%u" , &t); /* Reading secret key */

	N = (unsigned short) t;

	ctxt = "";

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
append_string(char *string, char char_to_append){
	char *temp;

	temp = (char *) malloc(sizeof(char) * (strlen(string) + 1));

	strcat(temp, string);

	string = "";

	strcat(temp, &char_to_append);

	return temp;
}

void 
perform_encryption() {
	char c,encrypted_c;
	int counter = 0;

	do {
		c = fgetc(plaintext);
		if (__VALID__(c))
		{
			encrypted_c = (char) caesar_encrypt(c, N);
			ctxt = append_string(ctxt, encrypted_c);

		} else if (!__ES_CH__(c)){
			/* If char is an escape character or a space, just ignore it.*/
			fprintf(stderr,"UNRECOGNISED CHARACTER %c: File stream contains unrecognised character.\nThis algorithm supports Numbers[0-9] and Letters[A-Za-z].\n", c);
			exit(0);
		}
	} while(c != EOF);

	fprintf(output, "%s", ctxt);

	fclose(plaintext);
	fclose(output);
}

void 
perform_decryption(){
	char c,decrypted_c;

	do {
		c = fgetc(plaintext);
		if (__VALID__(c))
		{
			decrypted_c = (char) caesar_decrypt(c, N);

			ctxt = append_string(ctxt, decrypted_c);

			printf("%c\n",c);
		}
		else if (!__ES_CH__(c))
		{
			/* If char is an escape character or a space, just ignore it.*/
			fprintf(stderr,"UNRECOGNISED CHARACTER %c: File stream contains unrecognised character.\nThis algorithm supports Numbers[0-9] and Letters[A-Za-z].\n", c);
			exit(0);
		}

	} while(c != EOF);

	fprintf(output, "%s", ctxt);

	fclose(plaintext);
	fclose(output);
}