CC = gcc
OPTION = -W -Wall -std=c89 -pedantic -O2
OBJET= ./Objet/
SOURCE= ./Source/
EXEC_FILES = $(OBJET)main.o $(OBJET)plateau.o $(OBJET)jeu.o $(OBJET)mlv.o $(OBJET)cellule.o $(OBJET)deroulement.o $(OBJET)joueur.o $(OBJET)ia.o $(OBJET)eval.o

all: clean clearscreen Reversi

Reversi: $(EXEC_FILES)
	$(CC) $(OPTION) `pkg-config --cflags MLV` `pkg-config --libs-only-other --libs-only-L MLV` $^ `pkg-config --libs-only-l MLV` -o $@

$(OBJET)%.o: $(SOURCE)%.c $(SOURCE)%.h
	mkdir -p $(OBJET)
	$(CC) $(OPTION) $< -c -o $@

clearscreen:
	clear

utilisation: 
	@echo "Usage : ./Reversi   --prof <profondeur souhaitée : obligatoirement au-dessus de 2>"
	@echo "--mode <mode : t pour terminal ou g pour MLV>"
	@echo "--bot : si on veut bot contre bot ou par défaut jouer"
	@echo "--min_max : Si on lance en min_max ou par défaut en alpha_beta"

pdf: create clean_pdf

create:
	pdflatex Presentation/presentation.tex presentation.pdf
	pdflatex Presentation/presentation.tex presentation.pdf

clean_pdf:
	rm -rf *.aux *.log *.out *.toc	*.snm *.nav

clean :
	rm -rf $(OBJET) *~ Reversi presentation.pdf
