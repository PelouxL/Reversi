#ifndef _EVAL_H_
#define _EVAL_H_

#include <stdlib.h>
#include <stdio.h>

#include "cellule.h"

#define COIN 10
#define BORD 5
#define NEUTRE 1

int evaluation_position(int **tab_points, l_cellule bornes, cellule coup);
/* evalue la position d'un pion et renvoie sa valeur */

void mini_max(arbre a);

cellule choix_poids(arbre a);

int alpha_beta(arbre a, int alpha, int beta);

cellule choix_alpha_beta(arbre a);

void liberer_tab(int **mat, int n);

int **init_tableau_points(int n);

#endif
