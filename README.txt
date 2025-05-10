Description :
-------------

Ce programme permet d'exécuter une partie du jeu "Reversi" en mettant en ligne
de commande ./Reversi ainsi que ses possible option.


Installation :
--------------

1. Faites "make" pour compiler le programme et créer l'exécutable 'Reversi' 

2. Assurez vous d'avoir les droit d'exécution du l'exécutable 'Reversi':
	chmod u+x Reversi

3. Possibilité d'afficher l'utilisation du make : make utilisation


Utilisation :
-------------

Pour lancer le programme, utilisez la commande suivante :

	./Reversi --prof --mode --bot --min_max


Options :
---------

--prof : Définit la profondeur de l'arbre ( --prof x | x >= 2)( obligatoire /!\)

--mode : Définit si on joue en mode graphique ou terminal ( --mode g/t )( optionnel )

--bot : Lance le programme avec deux ia, l'une contre l'autre (--bot )( optionnel )

--min_max : Sélection de l'algorithme voulu( --min_max | Alpha_beta de base )( optionnel )


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
