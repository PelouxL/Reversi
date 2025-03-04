#include <stdlib.h>
#include <stdio.h>
#include "types.h"

plateau * initialisation_plateau(int n){
  plateau * p = NULL;
  int i;

  if( (p = (plateau *) malloc (sizeof(plateau))) == NULL ){
    fprintf(stderr, "Erreur lors de l'allocation memoire\n");
    return NULL;
  }
  
  p -> n= n;
  
  if( (p -> mat = (int **) malloc (n *sizeof(int *))) == NULL ){
    fprintf(stderr, "Erreur lors de l'allocation memoire\n");
    return NULL;
  }
  
  for( i = 0 ; i < n ; i++ ){
    if( (p -> mat[i] = (int *) calloc (n , sizeof(int))) == NULL ){
      fprintf(stderr, "Erreur lors de l'allocation memoire\n");
      /* on libère toutes les cases allouer */
      for( i = i - 1 ; i >= 0 ; i++ ){
	free(p -> mat[i]);
      }
      return NULL;
    }
  }
  return p;
}


void vider_plateau( plateau *p){
  int i;
  for( i = 0 ; i < p -> n ; i++ ){
    free(p -> mat[i]);
  }
  free(p -> mat);
  free(p); /* il faut mettre le pointeur a NULL ? */
  
}

void affiche_plateau(plateau * p){
  int i, j;

  for( i = 0 ; i < p -> n ; i++ ){
    for( j = 0 ; j < p -> n ; j++){
      printf("%d ", p -> mat[i][j]);
    }
    printf("\n");
  }
}


/* permet de changer la couleur d'un pion */
void inserer_pions( plateau * p, int i, int j, int couleur){
  p -> mat[i][j] = couleur;
}
  
int main(){
  int i = 8;
  plateau * p = NULL;

  p = initialisation_plateau(i);
  inserer_pions(p, 4, 4, 1);
  affiche_plateau(p);
  printf("une fois afficher, on efface en memoire \n");
  vider_plateau(p);
  exit(EXIT_SUCCESS);
}
