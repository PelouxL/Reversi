#ifndef _JOUEUR_C_
#define _JOUEUR_C_

#include "joueur.h"

cellule recuperer_coup(plateau *p){

    char col;
    int lig;
    cellule coup;

    printf("Veuillez choisir un coup format lettre chiffre (ex: A1)\n");
    if((scanf("%c%d", &col, &lig) != 2)
       || col < 'A' || col >= 'A' + p->n || lig < 1 || lig > p->n){

        coup.x = -1;
        coup.y = -1;

        printf("Erreur lors de la saisie : %c%d\n", col, lig);
        viderBuffer();
    
        return coup;
    }
  
    coup.x = lig - 1;
    coup.y = col - 'A';
  
    printf("%d%d\n", coup.x, coup.y);
    viderBuffer();
  
    return coup;
}

plateau *jouer_coup_j(plateau *p, cellule coup){

    inserer_pions(p, coup.x, coup.y, p->j_couleur);
    printf("Pion  en %d %c \n", coup.x + 1, coup.y + 'A');
    
    return p;
}

#endif