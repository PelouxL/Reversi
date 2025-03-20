CC = gcc
OPTION = -W -Wall -std=c89 -pedantic -O2
OBJET= ./Objet/
SOURCE= ./Source/
EXEC_FILES = $(OBJET)main.o $(OBJET)plateau.o $(OBJET)jeu.o $(OBJET)mlv.o $(OBJET)cellule.o 

all: main

main: $(EXEC_FILES)
	$(CC) $(OPTION) `pkg-config --cflags MLV` `pkg-config --libs-only-other --libs-only-L MLV` $^ `pkg-config --libs-only-l MLV` -o $@

$(OBJET)%.o: $(SOURCE)%.c $(SOURCE)%.h
	mkdir -p $(OBJET)
	$(CC) $(OPTION) $< -c -o $@

clean :
	rm -rf $(OBJET) *~ main