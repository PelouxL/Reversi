#ifndef _JEU_H_
#define _JEU_H_

#include "cellule.h"
#include "plateau.h"

void retourner_pieces(plateau p, l_cellule l_cel, int coul);
/* Retourne les pieces du plateau dont les coordonnees ont ete passees en parametres dans la couleur indiquee */

int couleur_adverse(int couleur);
/* Renvoi la couleur de l'adversaire */

l_cellule coups_possibles(plateau p, int coul_j);
/* Renvoie la liste de cellules ou le joueur de la couleur passee en parametre peut poser un pion */

#endif