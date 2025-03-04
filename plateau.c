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
  char tab[8] ={'A','B','C','D','E','F','G','H'};

  /* ligne du dessus */
  printf("   ");
  for(i = 0 ; i < p -> n*2 ; i++){
    printf("-");
  }
  printf("\n");

  /* affichage des cases du plateau */
  for( i = 0 ; i < p -> n ; i++ ){
    printf("%d | ",i + 1); /* affichage des entiers des coordonne des cases */
    for( j = 0 ; j < p -> n ; j++){
      if( p -> mat[i][j] == 0){
	printf(". ");
      }if( p -> mat[i][j] == 1){
	printf("N ");
      }if( p -> mat[i][j] == 2){
	printf("B ");
      }
    }
    printf("|\n");
    
  }

  /* affichage de la ligne du dessous */
  printf("   ");
  for( i = 0 ; i <= p -> n * 2 ; i++ ){
    printf("-");
  }
  /* affichage des lettre pour les coordonnees des cases */
  printf("\n    ");
  for(i = 0 ; i < p -> n; i++){
    printf("%c ", tab[i]);
  }  
  printf("\n");
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
  inserer_pions(p, 5, 4, 2);
  affiche_plateau(p);
  printf("une fois afficher, on efface en memoire \n");
  vider_plateau(p);
  exit(EXIT_SUCCESS);
}
