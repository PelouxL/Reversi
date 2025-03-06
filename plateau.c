#include <stdlib.h>
#include <stdio.h>
#include "plateau.h"
#include "jeu.h"
#include "types.h"

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
  char tab[8] ={'A','B','C','D','E','F','G','H'};

  /****************************************/
  /* Penser a mettre un truc pour refresh */
  /****************************************/
  
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
      if( p -> mat[i][j] == VIDE){
	printf(". ");
      }if( p -> mat[i][j] == NOIR){
	printf("N ");
      }if( p -> mat[i][j] == BLANC){
	printf("B ");
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
    printf("%c ", tab[i]);
  }  
  printf("\n");
}


/* permet de changer la couleur d'un pion */
void inserer_pions(plateau *p, int i, int j, int couleur){
  p -> mat[i][j] = couleur;
}
/*
int main(){
  int n = 8;
  plateau *p = NULL;
  cellule *c = NULL;
  
  p = initialisation_plateau(n);
  inserer_pions(p, 4, 4, 1);
  inserer_pions(p, 5, 4, 2);
  affiche_plateau(p);
  
  c = ini_tab(2);
  c[0].x = 3;
  c[0].y = 1;
  c[1].x = 4;
  c[1].y = 1;

  retourner_pieces(p, c, 2, NOIR);
  affiche_plateau(p);
  printf("une fois afficher, on efface en memoire \n");
  vider_plateau(p);
  exit(EXIT_SUCCESS);
}
*/