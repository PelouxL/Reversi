#ifndef _JEU_H_
#define _JEU_H_

#include "cellule.h"
#include "plateau.h"


void viderBuffer();

l_cellule cellules_depart();
/* nom temporaire, cette fonction permet d'avoir es 4 cellules de base */
  
cellule reccuperer_cellule_j();
/* retourne une cellule que le joueur rentre a l main ( pour terminal )
   renvie -1 -1 si la cellule est pas bonne */

void retourner_pieces(plateau p, l_cellule l_cel, int coul);
/* Retourne les pieces du plateau dont les coordonnees ont ete passees en parametres dans la couleur indiquee */

int couleur_adverse(int couleur);
/* Renvoi la couleur de l'adversaire */

l_cellule coups_possibles(plateau p, int coul_j);
/* Renvoie la liste de cellules ou le joueur de la couleur passee en parametre peut poser un pion */

plateau *jouer_coup_j(plateau *p, l_cellule coup_dispo, cellule coup);
/* Insere dans le plateau le coup rentrer par le joueur si c'est disponible */

plateau *jouer_coup_ordi(plateau *p, l_cellule coup_dispo);
/* Fait jouer l'odinateur sans algo de reflexion */

#endif
