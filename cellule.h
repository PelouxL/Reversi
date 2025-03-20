#ifndef _CELLULE_H_
#define _CELLULE_H_

#include <stdlib.h>
#include <stdio.h>

typedef struct{
  int x;
  int y;
}cellule;

typedef struct{
    int n;
    cellule *cel;
}l_cellule;


void afficher_cel(l_cellule l_c);

l_cellule ajouter_cellule(l_cellule l_c, int x, int y);

l_cellule creer_l_cellule();

l_cellule concat_l_cellule(l_cellule l_c1, l_cellule l_c2);

l_cellule liberer_l_cellule(l_cellule l_c);

#endif

