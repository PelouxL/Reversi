#ifndef _IA_H_
#define _IA_H_

#include <stdlib.h>
#include <stdio.h>

#include "plateau.h"
#include "jeu.h"

typedef struct noeud{
    int points;
    plateau *p;
    int profondeur;
    cellule coup;
    struct noeud *descendance;
    struct noeud *suivant;
}noeud;

typedef noeud *arbre;

plateau *copie_plateau(plateau *p);

arbre creer_noeud(plateau *p);

arbre descendance(arbre a, int **tab_points);

arbre ajouter_fils(arbre a, int **tab_points, int i, int j);

void affiche_arbre(arbre a);
/* affiche l'arbre ainsi que ses fils */

arbre creer_arbre(plateau *p, int **tab_points, int prof);

/* plateau *eval(arbre a); */

void liberer_arbre(arbre a);

#endif
