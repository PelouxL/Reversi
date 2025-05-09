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

/* renvoie 1 si l_cellule est vide */
int est_l_c_vide(l_cellule l_c);

/*affiche toute les cellule d'une l_cellule*/
void afficher_cel(l_cellule l_c);

/*ajoute une cellule a une l_cellule si elle n'est pas déjà présente*/
l_cellule ajouter_cellule(l_cellule l_c, int x, int y);

/*crée une l_cellule et la renvoie*/
l_cellule creer_l_cellule();

/* concatene deux l_cellule sans copier les doublons */
l_cellule concat_l_cellule(l_cellule l_c1, l_cellule l_c2);

/* libere en mémoire la l_cellule*/
void liberer_l_cellule(l_cellule *l_c);

/* supprimer un element d'une l_cellule*/
l_cellule *supprimer_cellule(l_cellule *l_c, cellule coup);

/*renvoie 1 si un element appartiens a une l_cellule*/
int appartient_l_c(l_cellule l_c, cellule c);

    
#endif

