CFLAGS=-g -fsanitize=address -fsanitize=undefined -Wall -std=c99

run: ausgabe
	./test.sh

compile: fahrzeuge.c fahrzeuge.h ../02_datum/datum.c ../02_datum/datum.h
	gcc $(CFLAGS) fahrzeuge.c ../02_datum/datum.c -o fahrzeuge

ausgabe: compile
	./fahrzeuge fahrzeuge1.txt ausgabe1.txt
	./fahrzeuge fahrzeuge2.txt ausgabe2.txt

clean:
	rm -f fahrzeuge ausgabe1.txt ausgabe2.txt
