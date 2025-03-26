#ifndef _JEU_C_
#define _JEU_C_

#include "jeu.h"

void viderBuffer(){
  int c = 0;
  while (c != '\n' && c != EOF)
    {
      c = getchar();
    }

}

l_cellule cellules_depart(){
  l_cellule c;
  
  c = creer_l_cellule();
  c = ajouter_cellule(c, 3, 4);
  c = ajouter_cellule(c, 3, 5); 
  c = ajouter_cellule(c, 4, 4); 
  c = ajouter_cellule(c, 4, 5); 
  return c;
} 

cellule reccuperer_cellule_j(){
  char c;
  int lig, col;
  cellule cel;

  printf("Veuillez choisir une cellule format lettre chiffre ex A1\n");
  if( (scanf("%c%d",&c , &lig) != 2) || c < 'A' || c > 'H' || lig < 1 || lig > 8){
    printf("erreur lors de la saisie\n");
    cel.x = -1;
    cel.y = -1;
    return cel;
  }
  col = c - 'A';
  cel.x = lig - 1;
  cel.y = col;
  printf("%d %d\n", cel.x, cel.y);
  return cel;
}


void retourner_pieces(plateau p, l_cellule l_cel, int coul){
    
    int i, x, y;
    
    for (i = 0; i < l_cel.n; i++){
        x = l_cel.cel[i].x;
        y = l_cel.cel[i].y;
        p.mat[x][y] = coul;
    }
}


int couleur_adverse(int couleur){
    if(couleur == NOIR){
        return BLANC;
    }
    return NOIR;
}



/* Fonctions de calcul des coups possibles */
cellule suite(plateau p, int x_dep, int y_dep, int coul_adv, int dir_x, int dir_y){

    cellule cel;
    int i, j;
    
    i = x_dep+dir_x;
    j = y_dep+dir_y;

    /* on parcours les cellules jusqu'arriver soit en dehors du plateau soit sur une case vide ou qui de la couleur opposee */
    while ((i >= 0 && i < p.n) && (j >= 0 && j < p.n)
           && p.mat[i][j] == coul_adv){
        printf("      On regarde en %d%c\n", i+1, j+'A');
        i += dir_x;
        j += dir_y;
    }

    /* on verifie la raison de la sortie de la boucle while */
    if (i < 0 || i >= p.n || j < 0 || j >= p.n
        || p.mat[i][j] == couleur_adverse(coul_adv)){
        /* on renvoi une cellule "impossible" */
        cel.x = -1;
        cel.y = -1;
        printf("      Finalement non\n");
    } else {
        cel.x = i;
        cel.y = j;
        printf("------Tu pourras poser en %d%c\n", cel.x+1, cel.y+'A');
    }

    return cel;
    
}




l_cellule voisins(plateau p, int x_dep, int y_dep, int coul_j){

    int i, j, coul_adv;
    cellule cel;
    l_cellule l_cel;

    l_cel = creer_l_cellule();

    for (i = -1; i <= 1; i++){
        for (j = -1; j <= 1; j++){

            if ((x_dep+i >= 0 && x_dep+i < p.n) && (y_dep+j >= 0 && y_dep+j < p.n) /* on évite le seg fault */
                && p.mat[x_dep+i][y_dep+j] == (coul_adv = couleur_adverse(coul_j))){

                printf("   %d%c pourrait avoir une suite possible\n", x_dep+i+1, y_dep+j+'A');

                cel = suite(p, x_dep, y_dep, coul_adv, i, j);

                if (cel.x != -1 && cel.y != -1){
                    l_cel = ajouter_cellule(l_cel, cel.x, cel.y);
                
                }
                
            } else {
                printf("   Impossible de placer un pion dans la direction de %d%c\n", x_dep+i+1, y_dep+j+'A');
            }
        }
    }
    
    return l_cel;
}



l_cellule coups_possibles(plateau p, int coul_j){

    int i, j;
    l_cellule l_cel;

    l_cel = creer_l_cellule();

    for (i=0; i < p.n; i++){
        for (j=0; j < p.n; j++){

            if (p.mat[i][j] == coul_j){ /* la cases contient un pion du joueur actuel */
                printf("Je regarde pour %d%c : \n", i+1, j+'A');
                l_cel = concat_l_cellule(l_cel, voisins(p, i, j, coul_j));
            }         
        }
    }

    return l_cel;
        
}


plateau *jouer_coup_j(plateau *p, l_cellule coup_dispo, cellule coup){
  int i;
  for(i = 0; i < coup_dispo.n; i++){
    if(coup.x == coup_dispo.cel[i].x && coup.y  == coup_dispo.cel[i].y){
      inserer_pions(p, coup.x, coup.y, p->j_couleur);
      /* affichage pour les test, ça ne restera pas */
      printf("insertion faite en %d %c \n", coup.x + 1, coup.y + 'A');
      return p;
    }
  }
  printf("Coup non valide\n");
  return p;
}

plateau *jouer_coup_ordi(plateau *p, l_cellule coup_dispo){
    int choix;
    choix = rand()%coup_dispo.n;
    inserer_pions(p, coup_dispo.cel[choix].x,coup_dispo.cel[choix].y, p->ordi_couleur);
    return p;
}

#endif
