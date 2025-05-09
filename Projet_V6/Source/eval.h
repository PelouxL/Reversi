#ifndef _EVAL_H_
#define _EVAL_H_

#include <stdlib.h>
#include <stdio.h>

#include "cellule.h"

#define COIN 10
#define BORD 5
#define NEUTRE 1

/* evalue la position d'un pion et renvoie sa valeur */
int evaluation_position(int **tab_points, l_cellule bornes, cellule coup);

/* utilise l'algo min_max*/
void mini_max(arbre a);

/* retourne la cellule du meilleur coup après le passage de min_max */
cellule choix_poids(arbre a);

/* utilise l'algo alpha_beta retourne le meilleur coup possible*/
int alpha_beta(arbre a, int alpha, int beta);

/* choisis le meilleur coup enregistrer dans l'abre*/
cellule choix_alpha_beta(arbre a);

/* libere le tableau de points */
void liberer_tab(int **mat, int n);

/* initie le tableau de points */
int **init_tableau_points(int n);

#endif
