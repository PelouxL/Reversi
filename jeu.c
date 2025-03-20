#include <stdlib.h>
#include <stdio.h>
#include "plateau.h"
#include "types.h"

void retourner_pieces(plateau *p, cellule *t_coordonnees, int taille, int couleur){
    int i, x, y;
    for( i = 0 ; i < taille ; i++ ){
        x = t_coordonnees[i].x;
        y = t_coordonnees[i].y;
        p->mat[x][y] = couleur;
    }
}

l_cellule creer_l_cellule(){ 

    l_cellule l_c;

    l_c.n = 0;
    l_c.c = NULL;
    
    /* if((l_c.c = (cellule) malloc(sizeof(cellule))) == NULL){ */
    /*     fprintf(stderr,"Erreur d'allocation memoire l_cellule\n"); */
    /*     return NULL; */
    /* } */
    
    return l_c;
}

l_cellule ajouter_cellule(l_cellule l_c, int x, int y){

    if ((l_c.c = (cellule *) realloc(l_c.c, ++l_c.n * sizeof(cellule))) == NULL){
        fprintf(stderr,"Erreur de reallocation memoire l_cellule\n");
        exit(EXIT_FAILURE);
    }

    l_c.c[l_c.n-1]->x = x;
    l_c.c[l_c.n-1]->y = y;

    return l_c;
}


int couleur_adverse(int couleur){
    if(couleur == NOIR){
        return BLANC;
    }
    return NOIR;
}


/* POSER UN PION */

l_cellule coups_possibles(plateau p, int c){

    int i, j;
    l_cellule l_c;

    for (i=0; i<p->n; i++){
        for (j=0; j<p->n; j++){

            if (p->mat[i][j] == c){ /* la cases contient un pion du joueur actuel */
                /* check les cases autours */
            }

            
        }
    }
}

l_cellule voisins(plateau p, int x, int y, int c){

    int i, j, c_adv;
    l_cellule l_c;

    l_c = creer_l_cellule();

    for (i=-1; i<=1; i++){
        for (j=-1; j<=1; j++){

            if ((x+i >= 0 && x+i < p->n) && (y+j >= 0 && y+j < p->n) /* on évite le seg fault */
                && p->mat[x+i][y+j] == (c_adv = couleur_adverse(c))){

                /* on regarde la suite */

                /* l_c = ajouter_cellule(l_c, x+i, y+j); */
                
            }
            
        }
    }

    return l_c;
}

cellule suite(plateau p, int xd, int yd, int c_adv, int dx, int dy){

    cellule c;
    int i = xd+dx, j = yd+dy;

    while ((i >= 0 && i < p->n) && (j >= 0 && j < p->n)
           && p->mat[i][j] = c_adv){
        i += dx;
        j += dy;
    }

    if (i < 0 || i >= p->n || j < 0 || j >= p->n
        || p.mat[i][j] == couleur_adverse(c_adv)){
        c.x = -1;
        c.y = -1;
    } else {
        c.x = i;
        c.y = j;
    }

    return c;
    
}
