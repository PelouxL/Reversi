#ifndef _JOUEUR_H_
#define _JOUEUR_H_

#include "cellule.h"
#include "plateau.h"
cellule recuperer_coup(plateau *p);
/* retourne une cellule que le joueur rentre a l main ( pour terminal )
   renvie -1 -1 si la cellule est pas bonne */

plateau *jouer_coup_j(plateau *p, cellule coup, int tour);
/* Insere dans le plateau le coup rentrer par le joueur si c'est disponible */

#endif
