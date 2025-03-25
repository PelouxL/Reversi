#include "plateau.h"
#include "jeu.h"

plateau *commencer_la_partie(plateau *p){
   char commencer = 'A';
   
   while( commencer != 'N' && commencer != 'O' ){
    printf("Voulez vous commencez ? ( vous jourez les pions noirs ) O ou N\n");
    if( (scanf("%c", &commencer) != 1) || commencer != 'O' || commencer != 'N'){
      printf("erreur veuillez rentrez O ou N pour commencez\n");
      viderBuffer();
    }
  }
  if( commencer == 'O'){
    p->j_couleur = NOIR;
  }else{
    p->j_couleur = BLANC;
  }
  p->ordi_couleur = couleur_adverse( p->j_couleur );
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
    printf("%c ", 'A'+i);
  }  
  printf("\n");
}


/* permet de changer la couleur d'un pion */
void inserer_pions(plateau *p, int i, int j, int couleur){      
    p->mat[i][j] = couleur;
}
