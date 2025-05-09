#ifndef _IA_H_
#define _IA_H_

#include <stdlib.h>
#include <stdio.h>

#include "plateau.h"
#include "jeu.h"

/* Structure noeud */
typedef struct noeud{
    int points; /* poids attribue a chaque arbre */
    int profondeur; /* profondeur de l'arbre */
    cellule coup; /* coup joue a cette etape */
    l_cellule bornes; /* bornes qui serviront avec le coup a agir sur les pions entre */
    struct noeud *descendance; /* ensemble des fils de l'arbre */
    struct noeud *suivant; /* frere de l'arbre */
}noeud;

/* Type arbre */
typedef noeud *arbre;

/* Permet de copier un plateau */
plateau *copie_plateau(plateau *p);

/* Crée un noeud */
arbre creer_noeud();

/* Ajoute un fils a l'arbre */
arbre ajouter_fils(arbre a, int **tab_points, int i, int j, plateau *p);

/* Calcul le poids d'un fils */
void calcul_points(arbre fils, arbre a, int **tab_points, plateau *p);

/* Affiche un arbre */
void affiche_arbre(arbre a);

/* Crée un arbre */
arbre creer_arbre(plateau *p, int **tab_points, int prof);

/* Libère un arbre */
void liberer_arbre(arbre a);

#endif
