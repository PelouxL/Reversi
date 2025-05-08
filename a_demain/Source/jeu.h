#ifndef _JEU_H_
#define _JEU_H_

#include "cellule.h"
#include "plateau.h"

void viderBuffer();

plateau *cellules_depart(plateau *p);
/* nom temporaire, cette fonction permet d'avoir es 4 cellules de base */

l_cellule bornes_pieces_a_retourner(plateau *p, cellule coup);
/* Retourne les pieces du plateau dont les coordonnees ont ete passees en parametres dans la couleur indiquee */

void retourner_pieces(l_cellule bornes, plateau *p, int couleur, cellule coup);

int couleur_adverse(int couleur);
/* Renvoi la couleur de l'adversaire */

plateau *coups_possibles(plateau *p, int coul_j);
/* Renvoie la liste de cellules ou le joueur de la couleur passee en parametre peut poser un pion */

cellule choix_coup_ordi(plateau *p);
/* Fait jouer l'odinateur sans algo de reflexion */

int couleur_gagnante(plateau *p);
/* permet de savoir qu'elle couleur a gagnée */

int reste_coup(plateau *p);

void afficher_coup(plateau *p);

plateau *remise_a_zero(plateau *p);


#endif
