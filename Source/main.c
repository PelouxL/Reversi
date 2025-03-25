#include "main.h"

int main(){
  int n = 8;
  plateau *p = NULL;
  l_cellule c;
  cellule coup;

  /* MLV_create_window("Reversi", "Reversi", LX, LY); */
    
  p = initialisation_plateau(n);
  p = commencer_la_partie(p);
  
  printf("%d COULEUR %d\n", p->j_couleur , p->ordi_couleur);
    
  inserer_pions(p, 3, 'D' - 'A', NOIR);
  inserer_pions(p, 4, 'D' - 'A', BLANC);
  inserer_pions(p, 5, 'D' - 'A', BLANC);
  inserer_pions(p, 4, 'E' - 'A', BLANC);
  inserer_pions(p, 3, 'E' - 'A', NOIR);
  inserer_pions(p, 5, 'E' - 'A', NOIR);
  affiche_plateau(p);

  c = coups_possibles(*p, p->j_couleur);

  afficher_cel(c);
  coup = reccuperer_cellule_j();
  p = jouer_coup_j(p, c, coup);
  affiche_plateau(p); 
  /* affichage_mlv(p); */
  /* MLV_wait_seconds(10); */
  /* printf("une fois afficher, on efface en memoire \n"); */
  vider_plateau(p);
  /* MLV_free_window(); */

    
  exit(EXIT_SUCCESS);
}
