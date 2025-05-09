#ifndef _PLATEAU_C_
#define _PLATEAU_C_

#include "plateau.h"
#include <unistd.h>
#include "jeu.h"

plateau *commencer_la_partie(plateau *p, int *bot_vs_bot){
    char commencer = 'A';

    if (*bot_vs_bot == 1){
      p->j_couleur = rand() % 2 + 1;
      p->ordi_couleur = couleur_adverse(p->j_couleur);
    } else {
   
      while( commencer != 'N' &&  commencer != 'n' && commencer != 'O'  && commencer != 'o' /*&& commencer != 'B' && commencer != 'b'*/){
          printf("Voulez vous commencer ? ( vous jouerez les pions noirs ) O ou N\n"); /* \nVous pouvez aussi faire affronter deux ordinateur B\n*/
          if (scanf("%c", &commencer) != 1 || (commencer != 'O' && commencer != 'N' && commencer != 'n' && commencer != 'o'/*|| commencer != 'B' || commencer != 'b'*/)){
            fprintf(stderr, "erreur veuillez rentrer O ou N pour commencer\n");
          }
          viderBuffer();
      }

      if( commencer == 'O' || commencer == 'o'){
        p->j_couleur = NOIR;
      }else /*(commencer == 'N' || commencer == 'n')*/{
        p->j_couleur = BLANC;
      }/*else{
        p->j_couleur = rand()%2 + 1;
        *bot_vs_bot = 1;
      }*/
   
      p->ordi_couleur = couleur_adverse( p->j_couleur );
    }
    return p;
}

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


void restaurer_plateau(plateau *dest, plateau * src){
    int i, j;
    if (dest->n != src->n) return;  

    for (i = 0; i < dest->n; i++) {
        for (j = 0; j < dest->n; j++) {
            dest->mat[i][j] = src->mat[i][j];
        }
    }

    dest->j_couleur = src->j_couleur;
    dest->ordi_couleur = src->ordi_couleur;
}

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

void affiche_plateau(plateau *p){
  int i, j;

  /****************************************/
  /* Penser a mettre un truc pour refresh */
  /****************************************/
  if(system("clear") == 0){
     }
  
  /* ligne du dessus */
  printf("   ");
  for(i = 0 ; i <= p->n*2 ; i++){
    printf("_");
  }
  printf("\n");

  /* affichage des cellules du plateau */
  for( i = 0 ; i < p->n ; i++ ){
    printf("%d | ", i+1); /* affichage des entiers des coordonnees des cellules */
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

  /* affichage de la ligne du dessous */
  printf("   ");
  for( i = 0 ; i <= p->n*2 ; i++ ){
    printf("_");
  }
  /* affichage des lettres pour les coordonnees des cellules */
  printf("\n    ");
  for(i = 0 ; i < p->n; i++){
    printf("%c ", 'A'+i);
  }  
  printf("\n");
}


/* permet de changer la couleur d'un pion */
void inserer_pions(plateau *p, int i, int j, int couleur){      
    p->mat[i][j] = couleur;
}

#endif
