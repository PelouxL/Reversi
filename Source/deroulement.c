#ifndef _DEROULEMENT_C_
#define _DEROULEMENT_C_

#include "deroulement.h"

int jeu_terminal(plateau *p){
    cellule coup;
    int tour = 0, valide = 0, fin = 0, j_actuel, gagnant;
    
    p = cellules_depart(p);
    p = commencer_la_partie(p);

    /********************************************/
    /* Phase de placement des 4 premiers jetons */
    /********************************************/
    
    while(reste_coup(p)){

        tour++;
        j_actuel = tour%2 + 1;
        
        if (j_actuel == p->j_couleur){
            
            /* Tour du joueur */       
            while(valide != 1){
                affiche_plateau(p);
                printf("Vous avez le droit de jouez dans ces cellules ci-dessous :\n");
                afficher_coup(p);
                
                coup = recuperer_coup(p);
                if ((coup.x != -1 && coup.y != -1) && p->mat[coup.x][coup.y] == COUP){
                    valide = 1;
                }          
            }
            
            p = jouer_coup_j(p, coup);
            valide = 0;
            
        } else {
            /* Tour de l'ordi */
            printf("Tour de l'ordi\n");
            coup = choix_coup_ordi(p);
            inserer_pions(p, coup.x, coup.y, p->ordi_couleur);
        }
    }
    
    /***************************************/
    /* Phase de placement du jeu principal */
    /***************************************/
    do{
        tour++;
        j_actuel = tour%2 + 1;
        p = coups_possibles(p, j_actuel);
        affiche_plateau(p);
        if ((fin = reste_coup(p))){
            if(j_actuel == p->j_couleur){
                
                while(valide != 1){
                    afficher_coup(p);
                    coup = recuperer_coup(p);
                    if ((coup.x != -1 && coup.y != -1) && p->mat[coup.x][coup.y] == COUP){
                        valide = 1;
                    }    
                }
                
                p = jouer_coup_j(p, coup);
                retourner_pieces(p, coup);
                
                valide = 0;
                
            }else{
                printf("Tour de l'ordi\n");
                coup = choix_coup_ordi(p);
                inserer_pions(p, coup.x, coup.y, p->ordi_couleur);
                retourner_pieces(p, coup);
            }
        }
        p = remise_a_zero(p);
    }while(fin != 0);

    gagnant = couleur_gagnante(p);
    
    if(gagnant == p->j_couleur){
        printf("Bravo vous avez gagné(e) !\n");
    }else if(gagnant == p->ordi_couleur){
        printf("Aïe ! Vous avez perdu(e) !\n");
    }else{
        printf("Egalité !\n");
    }
    return 1;
}

#endif