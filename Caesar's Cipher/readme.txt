CSD3799 APOSTOLOS MAVROGIANNAKIS

To programma dexetai ws arguments to plaintext kai to operation pou prepei na kanoume

e.x.
./caesar [plaintext file] [operation]

*VALID OPERATIONS* : encryption/ENCRYPTION, decryption/DECRYPTION

*SIMANTIKO*
FORMAT TOU TEST:
[number which denotes shift]
[text
 to
 be
 encrypted/decrypted
 .
 .
 .]

__VALID__(c):
	Elenxei an o xarakthras C einai valid, diladi anikei stous xarakthres pou tha eprepe na dexomaste
	me vasi tin ekfwnisi tis askisis.

__OPER__(c):
	Epistrefei ti operation tha kanoume otan tre3oume to programma (encryption/decryption), me vasi to 
	deutero argument

__ES_CH__(c):
	Elegxei an o xarakthras c einai escape character kai epistrefei TRUE/FALSE

char vocabulary[]:
	Pinakas pou periexei olous tous valid xarakthres

void init():
	Kanei initialize oles tis metavlites mas, kai arxikopoiei to vocabulary.

char * append_string(...):
	Kanei append ena xaraktira se ena string kai to epistrefei

void perform_encryption:
	Kanei handle olo to encryption

void perform_decryption:
	Kanei handle olo to decryption

