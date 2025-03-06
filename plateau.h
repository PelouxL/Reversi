#include <stdlib.h>
#include <stdio.h>

#ifndef _PLATEAU_H_
#define _PLATEAU_H_

#define VIDE 0
#define NOIR 1
#define BLANC 2

typedef struct{
  int **mat; /* matrice carre ? */
  int n;
}plateau;

typedef struct{
  int x;
  int y;
}cellule;

typedef struct{
  int j_couleur;
  int ordi_cordi;
}couleur_j;

plateau *initialisation_plateau(int n);

void affiche_plateau(plateau *p);

void inserer_pions(plateau *p, int i, int j, int couleur);

void vider_plateau(plateau *p);

#endif