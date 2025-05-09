#ifndef _PLATEAU_H_
#define _PLATEAU_H_

#include<stdio.h>
#include<stdlib.h>

#define VIDE 0
#define NOIR 2
#define BLANC 1
#define COUP 10
#define RET 11

/* Structure Plateau */
typedef struct{
  int **mat; 
  int n;
  int j_couleur;
  int ordi_couleur;
}plateau;

/* Permet de choisir la couleur voulue sous version terminal */
plateau *commencer_la_partie(plateau *p, int *bot_vs_bot);

/* Initialisation plateau */
plateau *initialisation_plateau(int n);

/* Permet de free entièrement un plateau */
void vider_plateau(plateau *p);

/* Affichage du plateau */
void affiche_plateau(plateau *p);

/* Permet d'insérer un pion */
void inserer_pions(plateau *p, int i, int j, int couleur);

#endif
