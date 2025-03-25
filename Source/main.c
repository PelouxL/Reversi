#include "main.h"

int main(){
  int n = 8;
  plateau *p = NULL;
  l_cellule c;


  /* MLV_create_window("Reversi", "Reversi", LX, LY); */
    
  p = initialisation_plateau(n);
  p = commencer_la_partie(p);
  
  printf("%d COULEUR %d\n", p->j_couleur ,  p->ordi_couleur);
    
  inserer_pions(p, 4, 'D', NOIR);
  inserer_pions(p, 5, 'D', BLANC);
  inserer_pions(p, 6, 'D', BLANC);
  /* inserer_pions(p, 5, 'G', NOIR); */
  /* inserer_pions(p, 5, 'H', BLANC); */
  inserer_pions(p, 5, 'E', BLANC);
  inserer_pions(p, 4, 'E', NOIR);
  inserer_pions(p, 6, 'E', NOIR);
  affiche_plateau(p);

  /* c = creer_l_cellule(); */
  /* c = ajouter_cellule(c, 3, 1); */
  /* c = ajouter_cellule(c, 4, 1); */

  c = coups_possibles(*p, NOIR);

  afficher_cel(c);
  reccuperer_cellule_j();
  /* retourner_pieces(p, c.cel, c.n, NOIR);  */
  /* affiche_plateau(p); */
  /* affichage_mlv(p); */
  /* MLV_wait_seconds(10); */
  /* printf("une fois afficher, on efface en memoire \n"); */
  vider_plateau(p);
  /* MLV_free_window(); */

    
  exit(EXIT_SUCCESS);
}
