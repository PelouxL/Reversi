#ifndef _EVAL_C_
#define _EVAL_C_

#include <limits.h>

#include "ia.h"
#include "eval.h"


int est_coin(plateau *p, int i, int j){

  if((i == 0 || i == p->n) && (j == 0 || j == p->n)){
    return 1;  ;
  }
  return 0;
}

int est_bord(plateau *p, int i, int j){

   if(i == 0 || i == p->n || j == 0 || i == p->n){
     return 1;
   }
   return 0;
}

int **init_tableau_points(int n){
  int **tab_points = NULL, i, j;
  int tab[8][8] = {
    {100, -25,  10,   5,   5,  10, -25, 100},
    {-25, -50,  -2,  -2,  -2,  -2, -50, -25},
    { 10,  -2,   0,   0,   0,   0,  -2,  10},
    {  5,  -2,   0,   1,   1,   0,  -2,   5},
    {  5,  -2,   0,   1,   1,   0,  -2,   5},
    { 10,  -2,   0,   0,   0,   0,  -2,  10},
    {-25, -50,  -2,  -2,  -2,  -2, -50, -25},
    {100, -25,  10,   5,   5,  10, -25, 100},
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

void liberer_tab(int **tab_points, int n){
  int i;

  for(i = 0 ; i < n; i++){
    free(tab_points[i]);
  }
  free(tab_points);
}

int evaluation_position(int **tab_points, int i, int j){
  return tab_points[i][j];
}


void mini_max(arbre a){
  int acc = a->points;
  arbre courant = NULL;

  if(a != NULL){
    courant = a->descendance;
  }
  
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

plateau *choix_poids(arbre a){
  arbre courant = a->descendance;
  plateau *p = NULL;
  
  while(courant != NULL ){
    
    if(courant->points ==  a->points){
      if(p == NULL){
	p = courant->p;
      }
      if( p != NULL && rand()%2 == 1){
	p = courant->p;
      }
    }
    courant = courant->suivant;
  }
  return p;
}

int min(int a, int b){
  if(a < b){
    return a;
  }
  return b;
}

int max(int a, int b){
  if(a > b){
    return a;
  }
  return b;
}

int alpha_beta(arbre a, int alpha, int beta){
  int  v, score, bool = 1;
  arbre courant = NULL;

  if(a != NULL){
    courant = a->descendance;
  }

  if (courant == NULL) {
    return a->points; 
  }
  
  /* on regarde pour le max ( ordi ) */
  if(courant->profondeur%2 == 0){
    v = INT_MIN;
    while(courant != NULL){
	
      score = alpha_beta(courant, alpha, beta);
      if(score > v){
	v = score;
      }

      if(v >= beta){
	if(courant->suivant != NULL){
	  liberer_arbre(courant->suivant);
	  courant->suivant = NULL;        
	  courant = NULL;
	  bool = 0;
	}
      }else{
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
	
      score = alpha_beta(courant, alpha, beta);
      if(score < v){
	v = score;
      }

      if(v <= alpha){
	if(courant->suivant != NULL){
	  liberer_arbre(courant->suivant);
	  courant->suivant = NULL;        
	  courant = NULL;
	  bool = 0;
	}
      }else {
	if(v < beta){
	  beta = v;
	}
      }
      if(bool == 1){
	courant = courant->suivant;
      }
    }
  }
  a->points = v;
  return v;
}

plateau *choix_alpha_beta(arbre a){
  plateau *meilleur_plateau = NULL;
  arbre courant = a->descendance;
  int meilleur_score = INT_MIN;

  while(courant != NULL){
    if(courant->points > meilleur_score){
      meilleur_score = courant->points;
      meilleur_plateau = courant->p;
    }
    courant = courant->suivant;
  }
  return meilleur_plateau;
}
  

#endif
