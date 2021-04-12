CC=gcc
CFLAGS=-g -Wall
MAIN=caesar.c
HEADER=caesar_lib.h
EXEC=caesar

caesar: caesar.o
	$(CC) $(CFLAGS) -o $(EXEC) caesar.o

caesar.o: $(MAIN) $(HEADER)
	$(CC) -c $(MAIN) caesar.c

clean:
	rm -rf *.o
	rm -rf $(EXEC)
