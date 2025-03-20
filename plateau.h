#ifndef _PLATEAU_H_
#define _PLATEAU_H_

#define VIDE 0
#define NOIR 1
#define BLANC 2

typedef struct{
  int **mat; /* matrice carre ? */
  int n;
  int j_couleur;
  int ordi_cordi;
}plateau; /* variable globale ? */

plateau *initialisation_plateau(int n);

void affiche_plateau(plateau *p);

void inserer_pions(plateau *p, int i, int j, int couleur);

void vider_plateau(plateau *p);

#endif