#ifndef _DEROULEMENT_C_
#define _DEROULEMENT_C_

#include "deroulement.h"

int jeu_terminal(plateau *p){
    l_cellule c, r;
    cellule coup;
    int tour = 0, valide = 0, fin = 0, j_actuel;
    
    c = cellules_depart();
    p = commencer_la_partie(p);

    /********************************************/
    /* Phase de placement des 4 premiers jetons */
    /********************************************/
    
    while( est_l_c_vide(c) == 0){
        printf("%d val de lc et n = %d\n", est_l_c_vide(c), c.n);
        affiche_plateau(p);
        tour++;
        j_actuel = tour%2 + 1;
        if (j_actuel == p->j_couleur){
            /* Tour du joueur */
            printf("Vous avez le droit de jouez dans ces cellules ci-dessous :\n");
            afficher_cel(c);
        
            while(valide != 1){          
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
        j_actuel = tour%2 + 1;
        affiche_plateau(p);
        c = coups_possibles(*p, j_actuel);
        if (!(fin = est_l_c_vide(c))){
            printf("FIN EST EGAL A = %d\n", fin);
            if(j_actuel == p->j_couleur){
                
                while(valide != 1){
                    afficher_cel(c);
                    coup = reccuperer_cellule_j(p);
                    valide = appartient_l_c(c, coup);
                }
                p = jouer_coup_j(p, &c, coup);
                r = pieces_a_retourner(*p, coup, j_actuel);
                retourner_pieces(p, coup, r);
                liberer_l_cellule(&r);
                
                
                valide = 0;
                
            }else{
                printf("Tour de l'ordi\n");
                p = jouer_coup_ordi(p, &c) ;
            }
        }
    }while(fin == 0);
    
    return 1;
}

#endif