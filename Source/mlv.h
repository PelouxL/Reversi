#ifndef _MLV_H_
#define _MLV_H_

#include"plateau.h"
#include"cellule.h"
#include"jeu.h"
#include <MLV/MLV_all.h>

#define LX 1280
#define LY 720
#define L 20

typedef struct{
    int x;
    int y;
    int hauteur;
    int largeur;
    char txt[L];
} bouton;

int verif(bouton bouton, int coord_x, int coord_y);

int clic_bouton(bouton bout[], int lng);

void cree_bouton(bouton *bouton, char *message, int x, int y, MLV_Font *police);

void afficher_text(bouton bouton, MLV_Font *police);

void affichage_mlv(plateau *p);

void affiche_cellule_possible_mlv(char *message, int text_x, int text_y);

cellule obtenir_coord(plateau *p);

void afficher_coup_mlv(plateau *p);

plateau *inserer_pion_mlv(plateau *p, cellule c);

plateau *demande_premier_joueur(bouton bouton[], plateau *p);

#endif