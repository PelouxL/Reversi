#ifndef _JEU_H_
#define _JEU_H_

#include "types.h"

/* permet avec un tableau de coordonnees de retourner les pieces adverse */
void retourner_pieces(plateau *p, cellule *t_coordonnees, int taille, int couleur);

cellule * ini_tab(int n);

/* prend la couleur du j actuelle et renvoie celle de l'adversaire */
void couleur_adverse(int couleur);


#endif