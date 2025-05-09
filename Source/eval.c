#ifndef _EVAL_C_
#define _EVAL_C_

#include <limits.h>

#include "ia.h"
#include "eval.h"


/* initialise le tableau de l'importance de certaines positions*/
int **init_tableau_points(int n){
  int **tab_points = NULL, i, j;
  int tab[8][8] = {
    {150, -25,  10,   5,   5,  10, -25, 150},
    {-25, -50,  -2,  -2,  -2,  -2, -50, -25},
    { 10,  -2,   0,   0,   0,   0,  -2,  10},
    {  5,  -2,   0,   1,   1,   0,  -2,   5},
    {  5,  -2,   0,   1,   1,   0,  -2,   5},
    { 10,  -2,   0,   0,   0,   0,  -2,  10},
    {-25, -50,  -2,  -2,  -2,  -2, -50, -25},
    {150, -25,  10,   5,   5,  10, -25, 150},
  };


  if((tab_points = (int **) malloc (n * sizeof(int *))) == NULL){
    printf("Erreur lors de l'allocation du tableau de points\n");
    exit(EXIT_FAILURE);
  }

  for(i = 0; i < n; i++){
    if((tab_points[i] = (int *) malloc (n * sizeof(int ))) == NULL){
       printf("Erreur lors de l'allocation du tableau de points\n");
       
       for(i = i - 1 ; i >= 0; i++){
	 free(tab_points[i]);
       }
       free(tab_points);
       exit(EXIT_FAILURE);
    }
  }

  for(i = 0; i < n; i++){
    for(j = 0; j < n; j++){
      tab_points[i][j] = tab[i][j];
    }
  }
  return tab_points;
}

/* libere le tableau de points */
void liberer_tab(int **tab_points, int n){
  int i;

  for(i = 0 ; i < n; i++){
    free(tab_points[i]);
  }
  free(tab_points);
}

/* permet de connaitre combien de points vaut une position*/
int evaluation_position(int **tab_points, l_cellule bornes, cellule coup){
  int i, j, k,
    dir_x = 0, dir_y = 0, 
    acc = 0;

  for (k=0; k < bornes.n; k++){
      
    /* retrouver la direction */
    if (bornes.cel[k].x > coup.x){
      dir_x = 1;
    } else if (bornes.cel[k].x == coup.x){
      dir_x = 0;
    } else {
      dir_x = -1;
    }
        
    if (bornes.cel[k].y > coup.y){
      dir_y = 1;
    } else if (bornes.cel[k].y == coup.y){
      dir_y = 0;
    } else {
      dir_y = -1;
    }
    
    /* on calcule les points */
    acc += tab_points[coup.x][coup.y]; /* on évite de compter le coup plusieurs fois */
    for (i = coup.x + dir_x, j = coup.y + dir_y;
         i != bornes.cel[k].x || j != bornes.cel[k].y;
         i += dir_x, j += dir_y){
        /* on ajoute a acc les points du tab_points par rapport a sa position*/      
        acc += tab_points[bornes.cel[k].x][bornes.cel[k].y];
    }
  }
  return acc;
}

/*************************************************/
/******************** MIN_MAX ********************/
/*************************************************/

/* algo min max, permet a l'arbre de "reflechir" pour faire remonter les poids*/
void mini_max(arbre a){
  int acc = a->points;
  arbre courant = NULL;

  /* on vérifie si l'arbre n'est pas null*/
  if(a != NULL){
    courant = a->descendance;
  }
  
  /*si le noeud n'est pas null alors relance mini_max et on reccupere les points du noeud*/
  if(courant != NULL){
    mini_max(courant);
    acc = courant->points;
    courant = courant->suivant;
  }
  
  while(courant != NULL){
    mini_max(courant);
    /* on regarde pour le max ( ordi ) */
    if(courant->profondeur%2 == 0){
      if(courant->points > acc){
	acc = courant->points;
      
      }
      /* on regarde pour le min ( joueur ) */
    }else{
      if(courant->points < acc){
	acc = courant->points;
      }
    }
    
    courant = courant->suivant;
  }
  a->points = acc;
}

/* une fois mini_max effectuer, permet de savoir quel coup jouer par rapport au poids des fils*/
cellule choix_poids(arbre a){
    arbre courant = a->descendance;
    cellule coup;
    int oui = 0;
  
    while(courant != NULL ){
        /* si il y a plusieurs valeur geal on prends au départ la première recontrée*/
        if(courant->points ==  a->points){
            if(oui == 0){
                coup = courant->coup;
                oui = 1;
            }
            /* si même valeur rencontrée alors 50% de prendre celle la*/
            if( oui == 1 && rand()%2 == 1){
                coup = courant->coup;
            }
        }
        courant = courant->suivant;
    }
    return coup;
}
/* renvoie la valeur minimal entre a et b*/
int min(int a, int b){
  if(a < b){
    return a;
  }
  return b;
}
/* renvoie la valeur max entre a et b*/
int max(int a, int b){
  if(a > b){
    return a;
  }
  return b;
}

/**************************************************/
/******************* ALPHA_BETA *******************/
/**************************************************/
/* algo Alpha_beta return le meilleur poids pour l'arbre*/
int alpha_beta(arbre a, int alpha, int beta){
  int  v, score, bool = 1;
  arbre courant = NULL;
  /* verifie si a n'est pas null*/
  if(a != NULL){
    courant = a->descendance;
  }
  /* si on ets sur une feuille on return ses points*/
  if (courant == NULL) {
    return a->points; 
  }
  
  /* on regarde pour le max ( ordi ) */
  if(courant->profondeur%2 == 0){
    v = INT_MIN;
    while(courant != NULL){
      /* on reccupere le score du courant*/
      score = alpha_beta(courant, alpha, beta);
      /* si on trouve un score superieur alors on le garde */
      if(score > v){
	      v = score;
      }
      /* si notre poids le plus elever actuelle est plus gros que le prochain 
      fils a visiter alors on le libere et ne l'explore pas */
      if(v >= beta){
	      if(courant->suivant != NULL){
	        liberer_arbre(courant->suivant);
	        courant->suivant = NULL;        
	        courant = NULL;
	        bool = 0;
	      }
      }else{
        /* sinon on garde alpha */
	      if(v > alpha){
	        alpha = v;
	      }

      }
      if(bool == 1){
	      courant = courant->suivant;
      }
    }
    /* on regarde pour le min ( joueur ) */
  }else{
    v = INT_MAX;
    while(courant != NULL){
      /* on relance la fonction tant que on ets pas sur une feuille*/
      score = alpha_beta(courant, alpha, beta);
      /* on reccupere le score le plus petit*/
      if(score < v){
	      v = score;
      }
      /* si v est plus petit que lapha alors on libere l'arbre*/
      if(v <= alpha){
	      if(courant->suivant != NULL){
	      liberer_arbre(courant->suivant);
	      courant->suivant = NULL;        
	      courant = NULL;
	      bool = 0;
	    }
      }else {
        /* sinon beta prends la valeur de v*/
	      if(v < beta){
	       beta = v;
	      }
      }
      /* si la branche n'a pas été libérer alors on le visite */
      if(bool == 1){
	      courant = courant->suivant;
      }
    }
  }
  a->points = v;
  return v;
}

/* permet de choisir le coup a prendre en regardans dans l'arbre retourne une cellule */
cellule choix_alpha_beta(arbre a){
    arbre courant = a->descendance;
    int meilleur_score = INT_MIN;
    cellule meilleur_coup;
    /* on regarde tout les frère du courant*/
    while(courant != NULL){
        if(courant->points > meilleur_score){
            meilleur_score = courant->points;
            meilleur_coup = courant->coup;
        }
        courant = courant->suivant;
    }
    return meilleur_coup;
}
  

#endif
