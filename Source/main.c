#include "main.h"

int main(){
  int n = 8;
  plateau *p = NULL;

  /* MLV_create_window("Reversi", "Reversi", LX, LY); */

  
  p = initialisation_plateau(n);

  jeu_terminal(p);

  /* afficher_cel(c); */
  /* coup = reccuperer_cellule_j(); */
  /* p = jouer_coup_j(p, c, coup); */
  
  /* affiche_plateau(p); */

  /* c = coups_possibles(*p, p->ordi_couleur); */
  /* p = jouer_coup_ordi(p, c); */
  affiche_plateau(p);
  /* MLV_wait_seconds(10); */
  /* printf("une fois afficher, on efface en memoire \n"); */
  vider_plateau(p);
  /* MLV_free_window(); */

    
  exit(EXIT_SUCCESS);
}
