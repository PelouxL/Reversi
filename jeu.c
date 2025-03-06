#include "plateau.h"

void retourner_pieces(plateau *p, cellule *t_coordonnees, int taille, int couleur){
    int i, x, y;
    for( i = 0 ; i < taille ; i++ ){
        x = t_coordonnees[i].x;
        y = t_coordonnees[i].y;
        p->mat[x][y] = couleur;
    }
}

cellule * ini_tab(int n){ 
    cellule *c= NULL;
    if( (c = (cellule *) malloc(n * sizeof(cellule))) == NULL){
        fprintf(stderr,"Erreur d'allocation memoire\n");
        return NULL;
    }
    return c;
}


void couleur_adverse(int couleur){
    if(couleur == NOIR){
        return BLANC;
    }
    return NOIR;
}

    