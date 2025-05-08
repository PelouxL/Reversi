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

int est_l_c_vide(l_cellule l_c);

void afficher_cel(l_cellule l_c);

l_cellule ajouter_cellule(l_cellule l_c, int x, int y);

l_cellule creer_l_cellule();

l_cellule concat_l_cellule(l_cellule l_c1, l_cellule l_c2);

void liberer_l_cellule(l_cellule *l_c);

l_cellule *supprimer_cellule(l_cellule *l_c, cellule coup);

int appartient_l_c(l_cellule l_c, cellule c);

    
#endif

