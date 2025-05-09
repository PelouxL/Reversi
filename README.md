Description :
-------------

Ce programme permet d'executer une partie du jeu "Reversi" en mettant en ligne
de commande ./Reversi ainsi que ses possible option.


Installation :
--------------

1. Faites "make" pour compiler le programme et creer l'executable 'Reversi' 

2. Assurez vous d'avoir les droit d'éxecution du l'executable 'Reversi':
	chmod u+x Reversi


Utilisation :
-------------

Pour lancer le programme, utilisez la commande suivante :

	./Reversi --prof --mode --bot --algo


Options :
---------

--prof : Définit la profondeur de l'arbre ( --prof x | x >= 2)( obligatoire /!\)

--mode : Définit si on joue en mode graphique ou terminal ( --mode g/t )( optionnel )

--bot : Lance le programme avec deux ia, l'une contre l'autre (--bot o/n)( optionnel )

--help : Affiche le README sur le terminal ( optionnel )


Fichiers :
----------

Reversi		- Le programme exécutable
README.md	- Ce fichier
Source		- Contient l'ensemble des fichier .c et .h du programme

Auteur :
--------

RODRIGUES Paul 
DELAFORGE Jean
PELOUX Louis
