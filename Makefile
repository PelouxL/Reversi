CC = gcc
OPTION = -W -Wall -std=c89 -pedantic -O2

main: main.o plateau.o jeu.o mlv.o cellule.o
	$(CC) $(OPTION) `pkg-config --cflags MLV` `pkg-config --libs-only-other --libs-only-L MLV` main.o plateau.o jeu.o mlv.o cellule.o `pkg-config --libs-only-l MLV` -o main

main.o: main.c
	$(CC) $(OPTION) main.c -c

plateau.o: plateau.c plateau.h
	$(CC) $(OPTION) plateau.c -c

cellule.o: cellule.c cellule.h
	$(CC) $(OPTION) $< -c


jeu.o: jeu.c jeu.h
	$(CC) $(OPTION) jeu.c -c

mlv.o: mlv.c mlv.h
	$(CC) $(OPTION) mlv.c -c

clean :
	rm -rf *.o *~ main