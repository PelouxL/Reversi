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

/* Lancement de la version terminal */
int jeu_terminal(plateau *p, int prof, int bot_vs_bot, int min_max){
  cellule coup;
  arbre a = NULL, a_bis = NULL;
  int tour = 0, valide = 0, fin = 0, j_actuel, gagnant, meilleur;
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
          /* Joueur vs Bot */
          while(valide != 1){
              affiche_plateau(p);
              printf("Vous avez le droit de jouez dans ces cellules ci-dessous :\n");
              afficher_coup(p);
              
              coup = recuperer_coup(p);
              if ((coup.x != -1 && coup.y != -1) && p->mat[coup.x][coup.y] == COUP){
                  valide = 1;
              }          
          }
          /* Jouer le coup */
          p = jouer_coup_j(p, coup, j_actuel);
          valide = 0;
        }else{
          /* Bot vs Bot */
          coup = choix_coup_ordi(p);
          inserer_pions(p, coup.x, coup.y, p->j_couleur);
        }
      } else {
          /* Tour de l'ordi */
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

        /* Tour du joueur ou du deuxieme bot */
        if(bot_vs_bot == 0){

          /* Joueur vs Bot */
          while(valide != 1){
            afficher_coup(p);
            coup = recuperer_coup(p);
            if ((coup.x != -1 && coup.y != -1) && p->mat[coup.x][coup.y] == COUP){
              valide = 1;
            }    
          }

          /* Jouer le coup */
          p = jouer_coup_j(p, coup, j_actuel);
          bornes = bornes_pieces_a_retourner(p, coup);
          afficher_cel(bornes);
          retourner_pieces(bornes, p, p->j_couleur, coup); 
          valide = 0;
    
        }else{

          /* Bot vs Bot */
          a_bis = creer_arbre(p, tab_points, prof);

          if(min_max == 1){
            /* Calcul du meilleur coup */
            mini_max(a_bis);
            coup = choix_poids(a_bis);
          }
          else{
            /* Calcul du meilleur coup */
            alpha_beta(a_bis, INT_MIN, INT_MAX);
            affiche_plateau(p);  
            coup = choix_alpha_beta(a_bis);
          }
          MLV_wait_milliseconds(700);
          
          /* Jouer le coup */
          p = jouer_coup_j(p, coup, j_actuel);
          bornes = bornes_pieces_a_retourner(p, coup);
          retourner_pieces(bornes, p, p->j_couleur, coup);
          liberer_arbre(a_bis);
        }
              
      }else{
        /* Tour de l'ordi */
        a = creer_arbre(p, tab_points, prof);

        if(min_max == 1){
          /* Calcul du meilleur coup */
            mini_max(a);
            coup = choix_poids(a);
        }
        else{
          /* Calcul du meilleur coup pour l'ordinateur */
          meilleur = alpha_beta(a, INT_MIN, INT_MAX);
          printf("meilleur choix possible %d\n",meilleur);
          affiche_plateau(p);
          coup = choix_alpha_beta(a);
        }

        /* Jouer le coup */
        p = jouer_coup_j(p, coup, j_actuel);
        bornes = bornes_pieces_a_retourner(p, coup);
        retourner_pieces(bornes, p, p->ordi_couleur, coup);
        liberer_arbre(a);
      }
    }
    p = remise_a_zero(p);
  }while(fin != 0);

  /* Calcul du gagnant */
  gagnant = couleur_gagnante(p);
  
  liberer_tab(tab_points, 8);
  liberer_l_cellule(&bornes); 
  
  if(gagnant == p->j_couleur){
    printf("Bravo vous avez gagné(e) !\n");
  }else if(gagnant == p->ordi_couleur){
    printf("Aïe ! Vous avez perdu(e) !\n");
  }else{
    printf("Egalité !\n");
  }
  return 1;
}

/* Lancement de la version graphique */
void jeu_mlv(plateau *p, int prof, int bot_vs_bot, int min_max){
  cellule coup;
  int j_actuel, gagnant, text_width, text_height, meilleur;
  int tour = 0, valide = 0, fin = 0;
  bouton boutons[2];
  MLV_Font *police;
  int **tab_points = NULL;
  arbre a = NULL, a_bis = NULL;
  l_cellule bornes;
    
  tab_points = init_tableau_points(p->n);
  police = MLV_load_font("./Fonts/Letters for Learners.ttf", 150);

  /* Si Bot vs Bot alors on ne demande pas de choisir une couleur */
  p = cellules_depart(p);
  if(bot_vs_bot == 0){
    p = demande_premier_joueur(boutons, p);
  }
  else{
    p -> j_couleur = rand()%2 + 1;
    p -> ordi_couleur = couleur_adverse( p -> j_couleur );
  }
    
  /********************************************/
  /* Phase de placement des 4 premiers jetons */
  /********************************************/

  while(reste_coup(p) > 0){
    affiche_plateau(p);
    tour++;
    j_actuel = tour % 2 + 1;
    affichage_mlv(p, j_actuel, p -> j_couleur);
        
    if(j_actuel == p -> j_couleur){

      /* Tour du joueur ou du deuxieme bot */
      if(bot_vs_bot == 0){

        /* Joueur vs Bot */
        while(valide != 1){
          afficher_coup(p);
          coup = obtenir_coord(p);
          if((coup.x != -1 && coup.y != -1) && p -> mat[coup.x][coup.y] == COUP){
            valide = 1;
          }
        }
	      inserer_pions(p, coup.x, coup.y, p -> j_couleur);
	      valide = 0;
      
      /* Bot vs Bot */  
      }else{
	      coup = choix_coup_ordi(p);
	      inserer_pions(p, coup.x, coup.y, p ->j_couleur);
	      MLV_wait_milliseconds(500);
      }
    }else{

      /* Tour Ordi */
      coup = choix_coup_ordi(p);
      inserer_pions(p, coup.x, coup.y, p -> ordi_couleur);
    }
   
    MLV_actualise_window();
  }

  /***************************************/
  /* Phase de placement du jeu principal */
  /***************************************/

  do{
    affiche_plateau(p);
    tour++;
    j_actuel = tour % 2 + 1;
    p = coups_possibles(p, j_actuel);
    affichage_mlv(p, j_actuel, p -> j_couleur);
    if((fin = reste_coup(p))){
	    if(j_actuel == p -> j_couleur){

        /* Tour du joueur ou du deuxieme bot */
	      if(bot_vs_bot == 0){

          /* Joueur vs Bot */
	        while(valide != 1){   
	          coup = obtenir_coord(p);
            if((coup.x != -1 && coup.y != -1) && p -> mat[coup.x][coup.y] == COUP){
              valide = 1;
            }
          }
	            
          /* Jouer le coup */
          inserer_pions(p, coup.x, coup.y, p -> j_couleur);
          bornes = bornes_pieces_a_retourner(p, coup);
          retourner_pieces(bornes, p, p->j_couleur, coup);
	        valide = 0;
	  

	      }else{
	  
          /* Bot vs Bot */
	        a_bis = creer_arbre(p, tab_points, prof);

          if(min_max == 1){
            mini_max(a_bis);
            coup = choix_poids(a_bis);
          }
          else{
            /* Calcul du meilleur coup */
            meilleur = alpha_beta(a_bis, INT_MIN, INT_MAX);
            printf("meilleur choix possible %d\n",meilleur);
            affiche_plateau(p);
            coup = choix_alpha_beta(a_bis);
          }
              
          /* Jouer le coup */
          p = jouer_coup_j(p, coup, j_actuel);
          bornes = bornes_pieces_a_retourner(p, coup);
          retourner_pieces(bornes, p, p->j_couleur, coup);
          MLV_wait_milliseconds(500);
          liberer_arbre(a_bis);
        }
	  
	    }else{

        /* Tour de l'ordi */
        a = creer_arbre(p, tab_points, prof);

        if(min_max == 1){
          mini_max(a);
          coup = choix_poids(a);
        }
        else{
          /* Calcul du meilleur coup */
          meilleur = alpha_beta(a, INT_MIN, INT_MAX);
          printf("meilleur choix possible %d\n",meilleur);
          affiche_plateau(p);
          coup = choix_alpha_beta(a);
        }
      
        /* Jouer le coup */
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
  liberer_l_cellule(&bornes); 
     
  /* Calcul du gagnant */
  gagnant = couleur_gagnante(p);

  if(bot_vs_bot == 0){
    
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
  }

  MLV_free_font(police);
  MLV_actualise_window();
  MLV_free_window();
}

#endif
