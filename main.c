#include "main.h"


int main(){
    int n = 8;
    plateau *p = NULL;
    l_cellule c;

    MLV_create_window("Reversi", "Reversi", LX, LY);
    p = initialisation_plateau(n);
    inserer_pions(p, 4, 4, 1);
    inserer_pions(p, 5, 4, 2);
    affiche_plateau(p);

    c = creer_l_cellule();
    c = ajouter_cellule(c, 3, 1);
    c = ajouter_cellule(c, 4, 1);

    afficher_cel(c);
  
    retourner_pieces(p, c.cel, c.n, NOIR); 
    affiche_plateau(p);
    affichage_mlv(p);
    MLV_wait_seconds(10);
    printf("une fois afficher, on efface en memoire \n");
    vider_plateau(p);
    MLV_free_window();
    exit(EXIT_SUCCESS);
}