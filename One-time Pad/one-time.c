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
	char *keyword, *input_text;

	plaintext = fopen(argv[1], "r");


	if(plaintext == NULL) {
		perror("Error opening file.");
	}

	int i, file_size = 0;
	
	fseek(plaintext, 0, SEEK_END);
	input_size = ftell(plaintext);
	fseek(plaintext, 0, SEEK_SET);

	input_text = (char *) malloc(input_size);

	fread(input_text, 1, input_size, plaintext);

	keyword = "";

	keyword = keyword_generator(input_size);

	switch(__OPER__(argv[2])) {
		case ENCRYPT:
			output = fopen("encrypted.txt", "w");
			if(output == NULL) {
				perror("Error opening file.");
				exit(0);
			}

			printf("Performing encryption\n");
			ctxt = otp_encrypt(input_text, keyword);
			
			break;
		case DECRYPT:
			output = fopen("decrypted.txt", "w");
			if(output == NULL) {
				perror("Error opening file.");
				exit(0);
			}
			printf("Performing decryption\n");
			ctxt = otp_decrypt(input_text, keyword);

			break;
		default:
			perror("Arrrrgh! No man's land has been reached.\n");
			assert(0); /* No man's land. */
			exit(0);
	}


	fprintf(output, "%s", ctxt);

	fclose(plaintext);
	fclose(output);

	return 0;
}

char *
otp_encrypt(char *input_text, char *keyword) {
	int i = 0;
	char *s, *hex;
	char encrypted_c;

	while(i < input_size)
	{
		if (__VALID__(input_text[i]))
		{
			encrypted_c = keyword[i] ^ input_text[i];
			s = append_char(s, encrypted_c);
			
		} else if (!__ES_CH__(input_text[i])){
			/* If char is an escape character or a space, just ignore it.*/
			fprintf(stderr,"UNRECOGNISED CHARACTER %c: File stream contains unrecognised character.\nThis algorithm supports Numbers[0-9] and Letters[A-Za-z].\n", input_text[i]);
			exit(0);
		}

		i++;
	}

	return s;
}

char *
otp_decrypt(char *input_text, char *keyword) {
	int i = 0;
	char *s;
	char encrypted_c;

	s = "";
	while(i < input_size)
	{
		if (__VALID__(input_text[i]))
		{
			encrypted_c = keyword[i] ^ input_text[i];
			s = append_char(s, encrypted_c);

		} else if (!__ES_CH__(input_text[i])){
			/* If char is an escape character or a space, just ignore it.*/
			fprintf(stderr,"UNRECOGNISED CHARACTER %c: File stream contains unrecognised character.\nThis algorithm supports Numbers[0-9] and Letters[A-Za-z].\n", input_text[i]);
			exit(0);
		}

		i++;
	}

	return s;
}

char *
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


char * 
append_char(char *string, char char_to_append){
	char *temp;

	temp = (char *) malloc(sizeof(char) * (strlen(string) + 1));

	strcat(temp, string);

	string = "";

	if(__PRINTABLE__(char_to_append)) {
		strcat(temp, &char_to_append);
	} else {
		char *hex;
		sprintf((char *) char_to_append, "%02X", hex);
		printf("%s", hex);
	}

	return temp;
}