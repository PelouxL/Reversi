#ifndef _JEU_H_
#define _JEU_H_

#include "cellule.h"
#include "plateau.h"

void viderBuffer();

/* Renvoi le plateau avec les cellules de départ */
plateau *cellules_depart(plateau *p);

/* Renvoi la couleur inverse */
int couleur_adverse(int couleur);

/* Renvoi le nombre de coups possibles */
int reste_coup(plateau *p);

/* Liste les coups possible sur le terminal */
void afficher_coup(plateau *p);

/* Modifie le plateau pour enlever tout les coup possibles */
plateau *remise_a_zero(plateau *p);

/* Permet d'identifier les coups possibles pour un joueur donne */
plateau *coups_possibles(plateau *p, int coul_j);

/* choisi un coup aleatoire parmis les coups disponibles */
cellule choix_coup_ordi(plateau *p);

/* renvoi la liste des "bornes" qui serviront ensuite avec le coup pour faire des actions sur les cellules qui se situent entre */
l_cellule bornes_pieces_a_retourner(plateau *p, cellule coup);

/* retourne les pieces entre le coup et les bornes dans la couleur passee en parametre*/
void retourner_pieces(l_cellule bornes, plateau *p, int couleur, cellule coup);

/* appelee en fin de partie, permet de definir le gagnant ou si'l y a egalite */
int couleur_gagnante(plateau *p);

/* renvoi le score du joueur blanc */
int score_blanc(plateau *p);

/* renvoi le score du joueur noir */
int score_noir(plateau *p);

#endif