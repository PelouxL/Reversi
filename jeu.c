#include <stdlib.h>
#include <stdio.h>
#include "cellule.h"
#include "plateau.h"


void retourner_pieces(plateau p, l_cellule l_cel, int coul){
    
    int i, x, y;
    
    for (i = 0; i < l_cel.n; i++){
        x = l_cel.cel[i].x;
        y = l_cel.cel[i].y;
        p.mat[x][y] = coul;
    }
}

int couleur_adverse(int couleur){
    if(couleur == NOIR){
        return BLANC;
    }
    return NOIR;
}

/* Fonctions de calcul des coups possibles */
l_cellule coups_possibles(plateau p, int coul_j){

    int i, j;
    l_cellule l_cel;

    l_cel = creer_l_cellule();

    for (i=0; i < p.n; i++){
        for (j=0; j < p.n; j++){

            if (p.mat[i][j] == coul_j){ /* la cases contient un pion du joueur actuel */
                l_cel = concat_l_cellule(l_cel, voisins(p, i, j, coul_j));
            }         
        }
    }

    return l_cel;
        
}

l_cellule voisins(plateau p, int x_dep, int y_dep, int coul_j){

    int i, j, coul_adv;
    cellule cel;
    l_cellule l_cel;

    l_cel = creer_l_cellule();

    for (i = -1; i <= 1; i++){
        for (j = -1; j <= 1; j++){

            if ((x+i >= 0 && x+i < p->n) && (y+j >= 0 && y+j < p->n) /* on évite le seg fault */
                && p.mat[x_dep+i][y_dep+j] == (coul_adv = couleur_adverse(c))){

                cel = suite(p, x_dep, y_dep, coul_adv, i, j);

                if (cel.x != -1 && cel.y != -1){
                    l_cel = ajouter_cellule(l_cel, x_dep+i, y_dep+j);
                
            }
            
        }
    }

    return l_c;
}

cellule suite(plateau p, int x_dep, int y_dep, int coul_adv, int dir_x, int dir_y){

    cellule cel;
    int i = x_dep+dir_x,
        j = y_dep+dir_y;

    /* on parcours les cellules jusqu'arriver soit en dehors du plateau soit sur une case vide ou qui de la couleur opposee */
    while ((i >= 0 && i < p.n) && (j >= 0 && j < p.n)
           && p.mat[i][j] = coul_adv){
        i += dir_x;
        j += dir_y;
    }

    /* on verifie la raison de la sortie de la boucle while */
    if (i < 0 || i >= p.n || j < 0 || j >= p.n
        || p.mat[i][j] == couleur_adverse(coul_adv)){
        /* on renvoi une cellule "impossible" */
        cel.x = -1;
        cel.y = -1;
    } else {
        cel.x = i;
        cel.y = j;
    }

    return cel;
    
}
