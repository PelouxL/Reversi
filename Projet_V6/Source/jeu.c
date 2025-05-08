#ifndef _JEU_C_
#define _JEU_C_

#include "jeu.h"

#include "ia.h"
#include "eval.h"

void viderBuffer(){
  int c = 0;
  while (c != '\n' && c != EOF)
    {
      c = getchar();
    }

}

plateau *cellules_depart(plateau *p){

  p->mat[3]['D'-'A'] = COUP;
  p->mat[3]['E'-'A'] = COUP;
  p->mat[4]['D'-'A'] = COUP;
  p->mat[4]['E'-'A'] = COUP;
  
  return p;
}

int couleur_adverse(int couleur){
    if(couleur == NOIR){
        return BLANC;
    }
    return NOIR;
}


/* COUP */
int reste_coup(plateau *p){
    int i, j, acc = 0;

    for (i=0; i < p->n; i++){
        for (j=0; j < p->n; j++){
            if (p->mat[i][j] == COUP){
                acc++;
            }
        }
    }
    return acc;
}

void afficher_coup(plateau *p){
    int i, j;

    printf("Vous pouvez jouer en :");
    for (i=0; i < p->n; i++){
        for (j=0; j < p->n; j++){
            if (p->mat[i][j] == COUP){
                printf(" %c%d", j+'A', i+1);
            }
        }
    }
    printf("\n");
}

plateau *remise_a_zero(plateau *p){
    int i, j;

    for(i = 0; i < p->n; i++){
        for(j = 0; j < p-> n; j++){
            if( p->mat[i][j] == COUP){
                p->mat[i][j] = VIDE;
            }
        }
    }
    return p;
}


/* Fonctions de calcul des coups possibles */
plateau *suite(plateau *p, cellule c_depart, int coul_adv, int dir_x, int dir_y, int bout){

    int i, j, tag;

    i = c_depart.x+dir_x;
    j = c_depart.y+dir_y;

    if (bout == VIDE){
        tag = COUP;
    } else {
        tag = RET;
    }

    /* on parcours les cellules jusqu'arriver soit en dehors du plateau soit sur une case vide ou qui de la couleur opposee */
    while (i >= 0 && i < p->n && j >= 0 && j < p->n
           && p->mat[i][j] == coul_adv){
        /* printf("      On regarde en %d%c\n", i+1, j+'A'); */
        i += dir_x;
        j += dir_y;
    }

    /* printf("      fin while i = %d, j = %d\n", i, j); */
    
    /* si on a trouvé la condition d'arret 'bout' */
    if (i >= 0 && i < p->n && j >= 0 && j < p->n
        && p->mat[i][j] == bout){
        
        p->mat[i][j] = tag;
        /* printf("------Tu pourras poser en %d%c\n", i+1, j+'A'); */
           
    } /* else { */
    /*     printf("      Finalement non\n"); */
    /* } */

    return p;
    
}


plateau *voisins(plateau *p, cellule c_depart, int coul_j, int bout){

    int i, j, coul_adv;

    for (i = -1; i <= 1; i++){
        for (j = -1; j <= 1; j++){
            /* printf(" valeur des boucle %d et %d\n", i, j); */
            if (c_depart.x+i >= 0 && c_depart.x+i < p->n && c_depart.y+j >= 0 && c_depart.y+j < p->n /* on évite le seg fault */
                && p->mat[c_depart.x+i][c_depart.y+j] == (coul_adv = couleur_adverse(coul_j))){

                /* printf("   %d%c pourrait avoir une suite possible\n", c_depart.x+i+1, c_depart.y+j+'A'); */

                suite(p, c_depart, coul_adv, i, j, bout);
                
            } else {
                /* printf("   Impossible de placer un pion dans la direction de %d%c\n", c_depart.x+i+1, c_depart.y+j+'A'); */
            }
        }
    }
    return p;
}


plateau *coups_possibles(plateau *p, int coul_j){

    cellule c;
    int i, j;

    for (i=0; i < p->n; i++){
        for (j=0; j < p->n; j++){

            if (p->mat[i][j] == coul_j){ /* la cases contient un pion du joueur actuel */
                c.x = i;
                c.y = j;
                voisins(p, c, coul_j, VIDE);
            }         
        }
    }

    return p;
        
}

cellule choix_coup_ordi(plateau *p){
    
    int choix, i, j;
    cellule coup;
    l_cellule coup_dispo;

    coup_dispo = creer_l_cellule();

    /* recuperation des cases possibles */
    for(i=0; i < p->n; i++){
        for(j=0; j < p->n; j++){
            if(p->mat[i][j] == COUP){
                coup_dispo = ajouter_cellule(coup_dispo, i, j);
            }
        }
    }

    /* choix aleatoire du coup */
    choix = rand()%coup_dispo.n;
    coup.x = coup_dispo.cel[choix].x;
    coup.y = coup_dispo.cel[choix].y;
 
    /* inserer_pions(p, coup.x, coup.y, p->ordi_couleur); */

    
    
    /* retourner_pieces(p, coup); */
    
    return coup;
}

l_cellule bornes_pieces_a_retourner(plateau *p, cellule coup){

  int i, j,
    coul_j = p->mat[coup.x][coup.y],
    acc = 0;
  l_cellule bornes;

  bornes = creer_l_cellule();
  
  /* calcul des bornes pour le coup */
  voisins(p, coup, coul_j, coul_j);

  /* recuperation des cases possibles */
  for(i=0; i < p->n; i++){
    for(j=0; j < p->n; j++){

      if(p->mat[i][j] == RET){
	bornes = ajouter_cellule(bornes, i, j);
	acc++;
        p->mat[i][j] = coul_j;
      }
    }
  }

  return bornes;
}

void retourner_pieces(l_cellule bornes, plateau *p, int couleur, cellule coup){
  int i, j, k,
    dir_x = 0, dir_y = 0;

  for (k=0; k < bornes.n; k++){
      
    /* retrouver la direction */
    if (bornes.cel[k].x > coup.x){
      dir_x = 1;
    } else if (bornes.cel[k].x == coup.x){
      dir_x = 0;
    } else {
      dir_x = -1;
    }
        
    if (bornes.cel[k].y > coup.y){
      dir_y = 1;
    } else if (bornes.cel[k].y == coup.y){
      dir_y = 0;
    } else {
      dir_y = -1;
    }

    /* on retourne */
    for (i = coup.x, j = coup.y;
         i != bornes.cel[k].x || j != bornes.cel[k].y;
         i += dir_x, j += dir_y){
            
        p->mat[i][j] = couleur;
    }
  }
}

int couleur_gagnante(plateau *p){
    int i, j, noir = 0, blanc = 0;

    for(i = 0; i < p->n; i++){
        for(j = 0; j < p->n; j++){
            if(p->mat[i][j] == NOIR){ 
                noir++;
            }
            if (p->mat[i][j] == BLANC){
                blanc++;
            }
        }
    }

    if (blanc > noir){
        return BLANC;
    }

    if (noir > blanc){
        return NOIR;
    }

    return 0;
    
}

               
#endif
