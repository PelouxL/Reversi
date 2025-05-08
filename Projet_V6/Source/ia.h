#ifndef _IA_H_
#define _IA_H_

#include <stdlib.h>
#include <stdio.h>

#include "plateau.h"
#include "jeu.h"

typedef struct noeud{
    int points;
    int profondeur;
    cellule coup;
    l_cellule bornes;
    struct noeud *descendance;
    struct noeud *suivant;
}noeud;

typedef noeud *arbre;

plateau *copie_plateau(plateau *p);

arbre creer_noeud();

arbre descendance(arbre a, int **tab_points, plateau *p,  int prof, int k);

arbre ajouter_fils(arbre a, int **tab_points, int i, int j, plateau *p);

void calcul_points(arbre fils, arbre a, int **tab_points, plateau *p);

void affiche_arbre(arbre a);
/* affiche l'arbre ainsi que ses fils */

arbre creer_arbre(plateau *p, int **tab_points, int prof);

/* plateau *eval(arbre a); */
void liberer_arbre(arbre a);

#endif
