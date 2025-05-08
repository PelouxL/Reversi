#ifndef _DEROULEMENT_C_
#define _DEROULEMENT_C_

#include "deroulement.h"

#include "jeu.h"
#include "mlv.h"
#include "joueur.h"
#include "ia.h"
#include "eval.h"
#include <limits.h>
#include <unistd.h>

int jeu_terminal(plateau *p, int prof){
    cellule coup;
    arbre a = NULL, a_bis = NULL;
    int tour = 0, valide = 0, fin = 0, j_actuel, gagnant, meilleur, bot_vs_bot = 0;
    int **tab_points = NULL;
    l_cellule bornes;

    tab_points = init_tableau_points(p->n);
    
    p = cellules_depart(p);
    
    p = commencer_la_partie(p, &bot_vs_bot);

    /********************************************/
    /* Phase de placement des 4 premiers jetons */
    /********************************************/
    
    while(reste_coup(p) > 0){

        tour++;
        j_actuel = tour%2 + 1;
        
        if (j_actuel == p->j_couleur){
            
            /* Tour du joueur ou du deuxieme bot*/
	  if(bot_vs_bot == 0){
            while(valide != 1){
                affiche_plateau(p);
                printf("Vous avez le droit de jouez dans ces cellules ci-dessous :\n");
                afficher_coup(p);
                
                coup = recuperer_coup(p);
                if ((coup.x != -1 && coup.y != -1) && p->mat[coup.x][coup.y] == COUP){
                    valide = 1;
                }          
            }
            
            p = jouer_coup_j(p, coup, j_actuel);
            valide = 0;
	  }else{
	    
	     coup = choix_coup_ordi(p);
	     inserer_pions(p, coup.x, coup.y, p->j_couleur);
	    
	  }
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
	  if(bot_vs_bot == 0){
	    
	    while(valide != 1){
	      afficher_coup(p);
	      coup = recuperer_coup(p);
	      if ((coup.x != -1 && coup.y != -1) && p->mat[coup.x][coup.y] == COUP){
		valide = 1;
	      }    
	    }

	    p = jouer_coup_j(p, coup, j_actuel);
	    bornes = bornes_pieces_a_retourner(p, coup);
	    afficher_cel(bornes);
	    retourner_pieces(bornes, p, p->j_couleur, coup);
                
	    valide = 0;
	    
	  }else{
	    a_bis = creer_arbre(p, tab_points, prof);

	    meilleur = alpha_beta(a_bis, INT_MIN, INT_MAX);
	    printf("meilleur choix possible %d\n",meilleur);
	    affiche_plateau(p);  
	    coup = choix_alpha_beta(a_bis);
	    MLV_wait_milliseconds(700);
	    

	    p = jouer_coup_j(p, coup, j_actuel);
	    bornes = bornes_pieces_a_retourner(p, coup);
	    retourner_pieces(bornes, p, p->j_couleur, coup);

	    liberer_arbre(a_bis);
	  }
                
	}else{
	  printf("Tour de l'ordi \n");
	  a = creer_arbre(p, tab_points, prof);

	  meilleur = alpha_beta(a, INT_MIN, INT_MAX);
	  printf("meilleur choix possible %d\n",meilleur);
	  affiche_plateau(p);
	  coup = choix_alpha_beta(a);
	

	  p = jouer_coup_j(p, coup, j_actuel);
	  bornes = bornes_pieces_a_retourner(p, coup);
	  retourner_pieces(bornes, p, p->ordi_couleur, coup);

	  liberer_arbre(a);
	}
      }
      p = remise_a_zero(p);
    }while(fin != 0);

    gagnant = couleur_gagnante(p);
    
    liberer_tab(tab_points, 8);
    
    if(gagnant == p->j_couleur){
      printf("Bravo vous avez gagné(e) !\n");
    }else if(gagnant == p->ordi_couleur){
      printf("Aïe ! Vous avez perdu(e) !\n");
    }else{
      printf("Egalité !\n");
    }
    return 1;
}


void jeu_mlv(plateau *p, int prof){
  cellule coup;
  int j_actuel, gagnant, text_width, text_height, meilleur, bot_vs_bot = 1;
  int tour = 0, valide = 0, fin = 0;
  /*char text[50];*/
  bouton boutons[2];
  MLV_Font *police;
  int **tab_points = NULL;
  arbre a = NULL, a_bis = NULL;
  l_cellule bornes;
    
  tab_points = init_tableau_points(p->n);

  police = MLV_load_font("Letters for Learners.ttf", 150);

  p = cellules_depart(p);
  p = demande_premier_joueur(boutons, p);
    
  while(reste_coup(p) > 0){
    affichage_mlv(p);
    affiche_plateau(p);
        
    tour++;
    j_actuel = tour % 2 + 1;
        
    if(j_actuel == p -> j_couleur){

      if(bot_vs_bot == 0){
	while(valide != 1){
                
	  coup = obtenir_coord(p);       
	  if((coup.x != -1 && coup.y != -1) && p -> mat[coup.x][coup.y] == COUP){
	    valide = 1;
	  }
	}
	inserer_pions(p, coup.x, coup.y, p -> j_couleur);
	valide = 0;
	
      }else{
	coup = choix_coup_ordi(p);
	inserer_pions(p, coup.x, coup.y, p ->j_couleur);
	MLV_wait_milliseconds(500);
      }
    }else{
      coup = choix_coup_ordi(p);
      inserer_pions(p, coup.x, coup.y, p -> ordi_couleur);
    }
   
    MLV_actualise_window();
  }

  do{
    affiche_plateau(p);
      tour++;
      j_actuel = tour % 2 + 1;
      p = coups_possibles(p, j_actuel);
      affichage_mlv(p);
      if((fin = reste_coup(p))){
	if(j_actuel == p -> j_couleur){

	  if(bot_vs_bot == 0){
	    while(valide != 1){
                
	      coup = obtenir_coord(p);
                    
	      if((coup.x != -1 && coup.y != -1) && p -> mat[coup.x][coup.y] == COUP){
		valide = 1;
	      }
	    }
                
	    inserer_pions(p, coup.x, coup.y, p -> j_couleur);
	    bornes = bornes_pieces_a_retourner(p, coup);
	    retourner_pieces(bornes, p, p->j_couleur, coup);
                
	    valide = 0;
	  
	  }else{
	  
	    a_bis = creer_arbre(p, tab_points, prof);

	    meilleur = alpha_beta(a_bis, INT_MIN, INT_MAX);
	    printf("meilleur choix possible %d\n",meilleur);
	    affiche_plateau(p);
	      
	    coup = choix_alpha_beta(a_bis);

	    p = jouer_coup_j(p, coup, j_actuel);
	    bornes = bornes_pieces_a_retourner(p, coup);
	    retourner_pieces(bornes, p, p->j_couleur, coup);

	    
	    MLV_wait_milliseconds(500);
	    liberer_arbre(a_bis);
	  }
	  
	}else{

	  a = creer_arbre(p, tab_points, prof);
	
	  meilleur = alpha_beta(a, INT_MIN, INT_MAX);
	  printf("meilleur choix possible %d\n",meilleur);
	  affiche_plateau(p);
	  
	  coup = choix_alpha_beta(a);
	  p = jouer_coup_j(p, coup, j_actuel);
	  bornes = bornes_pieces_a_retourner(p, coup);
	  retourner_pieces(bornes, p, p->ordi_couleur, coup);
	  coup = choix_alpha_beta(a);

	  liberer_arbre(a);

	 
	  
	}
      }
      p = remise_a_zero(p);
    }while(fin != 0);
    
    liberer_tab(tab_points, 8);
     
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
