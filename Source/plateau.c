#ifndef _PLATEAU_C_
#define _PLATEAU_C_

#include "plateau.h"
#include <unistd.h>
#include "jeu.h"

/* Permet de choisir la couleur voulue sous version terminal */
plateau *commencer_la_partie(plateau *p, int *bot_vs_bot){
    char commencer = 'A';

    if (*bot_vs_bot == 1){
      p->j_couleur = rand() % 2 + 1;
      p->ordi_couleur = couleur_adverse(p->j_couleur);
    } else {
   
      while( commencer != 'N' &&  commencer != 'n' && commencer != 'O'  && commencer != 'o'){
          printf("Voulez vous commencer ? ( vous jouerez les pions noirs ) O ou N\n");
          if (scanf("%c", &commencer) != 1 || (commencer != 'O' && commencer != 'N' && commencer != 'n' && commencer != 'o')){
            fprintf(stderr, "erreur veuillez rentrer O ou N pour commencer\n");
          }
          viderBuffer();
      }

      if( commencer == 'O' || commencer == 'o'){
        p->j_couleur = NOIR;
      }else{
        p->j_couleur = BLANC;
      }
   
      p->ordi_couleur = couleur_adverse( p->j_couleur );
    }
    return p;
}

/* Initialisation plateau */
plateau * initialisation_plateau(int n){
  plateau *p = NULL;
  int i;

  if((p = (plateau *) malloc (sizeof(plateau))) == NULL){
    fprintf(stderr, "Erreur lors de l'allocation memoire\n");
    return NULL;
  }
  
  p->n = n;
  
  if( (p->mat = (int **) malloc (n *sizeof(int *))) == NULL ){
    fprintf(stderr, "Erreur lors de l'allocation memoire\n");
    free(p);
    printf("caca\n");
    p = NULL;
    return NULL;
  }
  
  for( i = 0 ; i < n ; i++ ){
    if( (p->mat[i] = (int *) calloc (n , sizeof(int))) == NULL ){
      fprintf(stderr, "Erreur lors de l'allocation memoire\n");
      /* on libere toutes les cases allouees */
      for( i = i - 1 ; i >= 0 ; i-- ){
	free(p->mat[i]);
        p->mat[i] = NULL;
      }
      
      free(p->mat);
      p->mat = NULL;
      free(p);
      p = NULL;
      return NULL;
    }
  }
  return p;
}

/* Permet de free entièrement un plateau */
void vider_plateau(plateau *p){
  int i;
  
  for( i = 0 ; i < p->n ; i++ ){
    free(p->mat[i]);
    p->mat[i] = NULL;
  }
  free(p->mat);
  p->mat = NULL;
  free(p);
  p = NULL; 
}

/* Affichage du plateau */
void affiche_plateau(plateau *p){
  int i, j;

  /* Clear de la fenêtre pendant la partie pour avoir qu'un seul plateau visible */
  if(system("clear") == 0){
     }
  
  /* Ligne du dessus */
  printf("   ");
  for(i = 0 ; i <= p->n*2 ; i++){
    printf("_");
  }
  printf("\n");

  /* Affichage des cellules du plateau */
  for( i = 0 ; i < p->n ; i++ ){
    printf("%d | ", i+1); /* Affichage des entiers des coordonnees des cellules */
    for( j = 0 ; j < p -> n ; j++){
        
        switch(p->mat[i][j]){    
        case NOIR:
            printf("N ");
            break;
        case BLANC:
            printf("B ");
            break;
        case COUP:
            printf("X ");
            break;
        default:
            printf(". ");
        }

    }
    printf("|\n");  
  }

  /* Affichage de la ligne du dessous */
  printf("   ");
  for( i = 0 ; i <= p->n*2 ; i++ ){
    printf("_");
  }
  /* Affichage des lettres pour les coordonnees des cellules */
  printf("\n    ");
  for(i = 0 ; i < p->n; i++){
    printf("%c ", 'A'+i);
  }  
  printf("\n");
}


/* Permet d'insérer un pion */
void inserer_pions(plateau *p, int i, int j, int couleur){      
    p->mat[i][j] = couleur;
}

#endif
