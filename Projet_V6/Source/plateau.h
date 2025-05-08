#ifndef _PLATEAU_H_
#define _PLATEAU_H_

#include<stdio.h>
#include<stdlib.h>

#define VIDE 0
#define NOIR 2
#define BLANC 1
#define COUP 10
#define RET 11

typedef struct{
  int **mat; 
  int n;
  int j_couleur;
  int ordi_couleur;
}plateau;

plateau *commencer_la_partie(plateau *p, int *bot_vs_bot);

plateau *initialisation_plateau(int n);

void restaurer_plateau(plateau *dest, plateau * src);

void affiche_plateau(plateau *p);

void inserer_pions(plateau *p, int i, int j, int couleur);

void vider_plateau(plateau *p);

#endif
