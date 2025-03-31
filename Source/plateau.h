#ifndef _PLATEAU_H_
#define _PLATEAU_H_

#include<stdio.h>
#include<stdlib.h>

#define VIDE 0
#define NOIR 2
#define BLANC 1

typedef struct{
  int **mat; /* matrice carre ? */
  int n;
  int j_couleur;
  int ordi_couleur;
}plateau; /* variable globale ? */

plateau *commencer_la_partie(plateau *p);

plateau *initialisation_plateau(int n);

void affiche_plateau(plateau *p);

void inserer_pions(plateau *p, int i, int j, int couleur);

void vider_plateau(plateau *p);

#endif
