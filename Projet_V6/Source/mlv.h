#ifndef _MLV_H_
#define _MLV_H_

#include <MLV/MLV_all.h>
#include"plateau.h"
#include"cellule.h"

/* Dimension fenêtre */
#define LX 1280
#define LY 720

#define L 20

/* Structure bouton */
typedef struct{
    int x;
    int y;
    int hauteur;
    int largeur;
    char txt[L];
} bouton;

/* Fonction qui verifie si le clic de la souris est dans le bouton */
int verif(bouton bouton, int coord_x, int coord_y);

/* Fonction qui verifie si le clic de la souris est dans un des boutons et retour la valeur */
int clic_bouton(bouton bout[], int lng);

/* Fonction qui cree un bouton */
void cree_bouton(bouton *bouton, char *message, int x, int y, MLV_Font *police);

/* Fonction qui affiche le texte du bouton */
void afficher_text(bouton bouton, MLV_Font *police);

/* Fonction qui affiche le plateau de jeu */
void affichage_mlv(plateau *p, int tour, int couleur);

/* Fonction qui récupère les coordonnées d'un clic */
cellule obtenir_coord(plateau *p);

/* Fonction qui permet de choisir la couleur voulue */
plateau *demande_premier_joueur(bouton bouton[], plateau *p);

#endif
