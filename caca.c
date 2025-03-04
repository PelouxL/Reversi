#include "types.h"

cases *cases_vide_adj(plateau p, cases c){
    
    int i, j;

    for (i=-1; i <= 1; i++){
        for (j=-1; j <= 1; j++){

            if (
            
        
        }
    }

    
    
}

cases *verif_case(plateau p, int couleur){

    int i, j, nb_c_vide;
    cases *c_vide;

    for (i=0; i < p->n; i++){
        for (j=0; j < p->n; j++){

            if (p->m[i][j] == couleur){

                cases_vide_adj(p->m[i][j]);
                
            }
            
            
            
        }        
    }
}