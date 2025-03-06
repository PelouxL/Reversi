#include "types.h"

/* FAIRE UNE FONCTION C_*AC */

int suite(int x, int y, int i, int j, int couleur){

    while (((x+=i) >= 0 && x <= p->n)
           && ((y+=j) >= 0 && y <= p->n)
    
}

cellule *cases_vide_adj(plateau p, int x, int y){
    
    int i, j,
        c_adv;

    c_adv = couleur_adverse(c_j);
    
    /* controle des cellules voisines de c */
    for (i=-1; i <= 1; i++){
        for (j=-1; j <= 1; j++){

            /* verification des coordonnees pour ne pas se retrouver en dehors du plateau et ne pas controler la cellule (x,y) */
            if ((x+i >= 0 && x+i <= p->n)
                && (y+j >= 0 && y+j <= p->n)
                && !(i == 0 && j == 0)){

                /* si une cellule voisine correspond a la couleur adverse alors on regarde les suivantes dans la meme direction */
                if (p->mat[x+i][y+j] == c_adv){
                    suite()
                }
            }
        }
    }
}

cellule *verif_case(plateau p, int c_j){

    int i, j,
        nb_c_vide;
    cellule *c_vide;
    
    /* parcours de chaque cellules du plateau */
    for (i=0; i < p->n; i++){
        for (j=0; j < p->n; j++){

            /* on cherche des cellules de la couleur du joueur */
            if (p->m[i][j] == c_j){

                cases_vide_adj(p->m[i][j]);
                
            }
            
            
            
        }        
    }
}