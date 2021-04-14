#include "one-time_lib.h"

/* 
	One-time Pad:
		The One-Time-Pad (OTP) algorithm is a very simple but yet very strong algorithm in the sense
		that it can not be cracked even with quantum computers. The algorithm pairs each plaintext with
		a random secret key (also referred to as a one-time pad). Specifically, each bit or byte/character
		of the plaintext is combined with the corresponding bit or byte/character from the random secret
		key. One-time pad requires that the secret key is of the same size or longer than the plaintext.
*/

int 
main(int argc, char* argv[]) {
	unsigned char *keyword, *input_text, *plaintext;
	int i;

	f_plaintext = fopen(argv[1], "r");


	if(f_plaintext == NULL) {
		perror("Error opening file.");
	}


	// reading input
	input_text = read_input(f_plaintext);

	keyword = "";
	plaintext = NULL;
	ctxt = NULL;

	keyword = keyword_generator(strlen(input_text));

	output = fopen("encrypted.txt", "w");
	if(output == NULL) {
		perror("Error opening file.");
		exit(0);
	}
	printf("Plaintext(%ld): %s -> ", strlen(input_text),input_text);
	for(int i = 0; i < strlen(input_text); i++) {
		printf("%02X ", (unsigned int) input_text[i]);
	}
	printf("\n");
	printf("Performing encryption\n");
	i = 0;
	while(i < strlen(input_text)) {
		unsigned int c = otp_encrypt(input_text[i], keyword[i]);
		ctxt = append_char(ctxt, c);
		i++;
	}
	printf("CIPHER: %s -> ", ctxt);
	for(int i =0; i < strlen(ctxt); i++) {
		printf("%02X ", ctxt[i]);
	}
	printf("\n");

	for(int i = 0;i < strlen(input_text);i++) {
		unsigned int c = otp_decrypt(ctxt[i], keyword[i]);

		plaintext = append_char(plaintext, c);
	}

	printf("BACK TO PLAINTEXT: %s -> \n", plaintext);
	for(int i = 0; i < strlen(plaintext); i++) {
		printf( "%02X ", plaintext[i]);
	}
	printf("\n");

	fclose(f_plaintext);
	fclose(output);

	return 0;
}

unsigned int
otp_encrypt(char c, char k) {
	char encrypted_c;


	if (__VALID__(c))
	{
		encrypted_c = c ^ k;
			
	} else if (!__ES_CH__(c)){
		/* If char is an escape character or a space, just ignore it.*/
		fprintf(stderr,"UNRECOGNISED CHARACTER: File stream contains unrecognised character.\nThis algorithm supports Numbers[0-9] and Letters[A-Za-z].\n");
		exit(0);
	}
	return (unsigned int) encrypted_c;
}

unsigned int
otp_decrypt(char c, char k) {
	char decrypted_c;

	decrypted_c = c ^ k;

	return (unsigned int) decrypted_c;
}

unsigned char *
keyword_generator(int size)
{
	int i = 0;
	char *s;
	FILE* urand = fopen("/dev/urandom","r");

	s = "";
	while(i < size) {
		char rand_char;
		rand_char = fgetc(urand);

		s = append_char(s, rand_char);
		i++;
	}
	return s;
}


unsigned char *
append_char(unsigned char *string, char c){
	char *new;
	if(string == NULL) {
		new = (char *) malloc(sizeof(char)*2);
		new = strdup( &c);
	} else {
		new = (char *) malloc(sizeof(char)*(strlen(string)+2));

		strncat(new, string, strlen(string));
		strcat(new, &c);
	}

	return new;
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