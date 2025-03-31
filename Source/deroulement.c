#ifndef _DEROULEMENT_C_
#define _DEROULEMENT_C_

#include "deroulement.h"

int jeu_terminal(plateau *p){
    l_cellule c;
    cellule coup;
    int verif_fin = 0, tour = 0, valide = 0;
    
    c = cellules_depart();
    p = commencer_la_partie(p);

    /********************************************/
    /* Phase de placement des 4 premiers jetons */
    /********************************************/
    
    while( est_l_c_vide(c) == 0){
        printf("%d val de lc et n = %d\n", est_l_c_vide(c), c.n);
        affiche_plateau(p);
        tour++;

        if (tour%2 + 1 == p->j_couleur){
            /* Tour du joueur */
            printf("Vous avez le droit de jouez dans ces cellules ci-dessous :\n");
            afficher_cel(c);
        
            while( valide != 1){          
                coup = reccuperer_cellule_j(p);
                valide = appartient_l_c(c, coup);
                
            }
            
            p = jouer_coup_j(p, &c, coup);
            valide = 0;
        } else {
            /* Tour de l'ordi */
            printf("Tour de l'ordi\n");
            p = jouer_coup_ordi(p, &c) ;
        }
    }
    
    /***************************************/
    /* Phase de placement du jeu principal */
    /***************************************/
    do{
        tour++;
        affiche_plateau(p);
         if (tour%2 + 1 == p->j_couleur){
             c = coups_possible(


    }while(est_l_c_vide(c) == 0);
    
    return 1;
}

#endif