#ifndef _TYPES_H_
#define _TYPES_H_

/* pour mlv */
#define LX 1280
#define LY 720

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

#endif