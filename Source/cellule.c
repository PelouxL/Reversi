#ifndef _CELLULE_C_
#define _CELLULE_C_
#include "cellule.h"

void afficher_cel(l_cellule l_c){
    
    int i;
    for( i = 0; i < l_c.n ; i++ ){
        printf("%d%c, ", l_c.cel[i].x+1, l_c.cel[i].y+'A');
    }
    printf("\n");
}

l_cellule creer_l_cellule(){ 
    l_cellule  l_c;
    l_c.n = 0;
    l_c.cel = NULL;
    return l_c;
}

l_cellule ajouter_cellule(l_cellule l_c, int x, int y){
    
    l_c.n++;
    
    if ((l_c.cel = (cellule *) realloc(l_c.cel, l_c.n * sizeof(cellule))) == NULL){
        fprintf(stderr,"Erreur de reallocation memoire l_cellule\n");
        exit(EXIT_FAILURE);
    }

    l_c.cel[l_c.n-1].x = x;
    l_c.cel[l_c.n-1].y = y;

    return l_c;
}




l_cellule concat_l_cellule(l_cellule l_c1, l_cellule l_c2){
    int i, j, ajout;

    if(l_c1.n == 0){
        return l_c2;
    }
    
    for(i = 0; i < l_c2.n; i++){
    
        ajout = 1;
        
        for(j = 0; j < l_c1.n; j++){
                
            if(l_c2.cel[i].x == l_c1.cel[j].x && l_c2.cel[i].y == l_c1.cel[j].y){
                ajout = 0;
            }
        }
        
        if(ajout == 1){
            l_c1 = ajouter_cellule(l_c1, l_c2.cel[i].x, l_c2.cel[i].y);
        }
        
    }

    liberer_l_cellule(l_c2);
    
    return l_c1;
}

void liberer_l_cellule(l_cellule l_c){
    free(l_c.cel);
}


#endif