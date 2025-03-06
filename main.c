#include <stdlib.h>
#include <stdio.h>
#include <MLV/MLV_all.h>
#include "plateau.h"
#include "jeu.h"
#include "types.h"
#include "mlv.h"

int main(){
  int n = 8;
  plateau *p = NULL;
  cellule *c = NULL;

  MLV_create_window("Reversi", "Reversi", LX, LY);
  
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
  affichage_mlv(p);
  MLV_wait_seconds(10);
  printf("une fois afficher, on efface en memoire \n");
  vider_plateau(p);
  MLV_free_window();
  exit(EXIT_SUCCESS);
}