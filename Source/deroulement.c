#ifndef _DEROULEMENT_C_
#define _DEROULEMENT_C_

#include "deroulement.h"
#include "mlv.h"
#include "joueur.h"

int jeu_terminal(plateau *p){
    cellule coup;
    int tour = 0, valide = 0, fin = 0, j_actuel, gagnant;
    
    p = cellules_depart(p);
    p = commencer_la_partie(p);

    /********************************************/
    /* Phase de placement des 4 premiers jetons */
    /********************************************/
    
    while(reste_coup(p) > 0){

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

void jeu_mlv(plateau *p){
    cellule coup;
    int j_actuel, gagnant, text_width, text_height;
    int tour = 0, valide = 0, fin = 0;
    bouton boutons[2];
    MLV_Font *police;

    police = MLV_load_font("Letters for Learners.ttf", 150);

    p = cellules_depart(p);
    p = demande_premier_joueur(boutons, p);
    
    while(reste_coup(p) > 0){
        printf("%d\n", reste_coup(p));
        affichage_mlv(p);
        
        tour++;
        j_actuel = tour % 2 + 1;
        
        if(j_actuel == p -> j_couleur){
            while(valide != 1){
                
                coup = obtenir_coord(p);
                
                if((coup.x != -1 && coup.y != -1) && p -> mat[coup.x][coup.y] == COUP){
                    valide = 1;
                }
            }
            inserer_pions(p, coup.x, coup.y, p -> j_couleur);
            valide = 0;
        }
        else{
            printf("Tour Ordi\n");
            coup = choix_coup_ordi(p);
            inserer_pions(p, coup.x, coup.y, p -> ordi_couleur);
            printf("[%c - %d]\n", coup.x + 'A', coup.y);
        }
        MLV_actualise_window();
    }

    do{
        tour++;
        j_actuel = tour % 2 + 1;
        p = coups_possibles(p, j_actuel);
        affichage_mlv(p);
        if((fin = reste_coup(p))){
            if(j_actuel == p -> j_couleur){
                while(valide != 1){
                
                    coup = obtenir_coord(p);
                    
                    if((coup.x != -1 && coup.y != -1) && p -> mat[coup.x][coup.y] == COUP){
                        valide = 1;
                    }
                }
                inserer_pions(p, coup.x, coup.y, p -> j_couleur);
                retourner_pieces(p, coup);
                valide = 0;
            }
            else{
                printf("Tour Ordi\n");
                coup = choix_coup_ordi(p);
                inserer_pions(p, coup.x, coup.y, p -> ordi_couleur);
                retourner_pieces(p, coup);
            }
        }
        p = remise_a_zero(p);
    }while(fin != 0);

    gagnant = couleur_gagnante(p);
    
    if(gagnant == p->j_couleur){
        MLV_get_size_of_adapted_text_box_with_font("VOUS AVEZ GAGNE !", police, 10, &text_width, &text_height);
        MLV_draw_adapted_text_box_with_font( (LX - text_width) / 2, (LY - text_height) / 2, "VOUS AVEZ GAGNE !", police, MLV_ALPHA_TRANSPARENT, 0, MLV_COLOR_BLACK, MLV_rgba(235, 193, 132, 255), MLV_TEXT_CENTER);
        MLV_actualise_window();
        MLV_wait_seconds(3);
         
        
    }else if(gagnant == p->ordi_couleur){
        MLV_get_size_of_adapted_text_box_with_font("VOUS AVEZ PERDU !", police, 10, &text_width, &text_height);
        MLV_draw_adapted_text_box_with_font( (LX - text_width) / 2, (LY - text_height) / 2, "VOUS AVEZ PERDU !", police, MLV_ALPHA_TRANSPARENT, 0, MLV_COLOR_BLACK, MLV_rgba(235, 193, 132, 255), MLV_TEXT_CENTER);
        MLV_actualise_window();
        MLV_wait_seconds(3);
        
    }else{
        MLV_get_size_of_adapted_text_box_with_font("EGALITE !", police, 10, &text_width, &text_height);
        MLV_draw_adapted_text_box_with_font( (LX - text_width) / 2, (LY - text_height) / 2, "EGALITE !", police, MLV_ALPHA_TRANSPARENT, 0, MLV_COLOR_BLACK, MLV_rgba(235, 193, 132, 255), MLV_TEXT_CENTER);
        MLV_actualise_window();
        MLV_wait_seconds(3);
    }

    MLV_free_font(police);
    MLV_actualise_window();
    MLV_free_window();
}

#endif