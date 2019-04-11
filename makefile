all: hangman.x

hangman.x: client.o hangman.o
	gcc -std=c99 client.o hangman.o -o hangman.x

client.o: client.c hangman.c hangman.h
	gcc -std=c99 -c client.c
	
hangman.o: hangman.c hangman.h
	gcc -std=c99 -c hangman.c

clean:
	rm *.x *.o