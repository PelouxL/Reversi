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

/* Renvoi le plateau avec les cellules de départ */
plateau *cellules_depart(plateau *p){

  p->mat[3]['D'-'A'] = COUP;
  p->mat[3]['E'-'A'] = COUP;
  p->mat[4]['D'-'A'] = COUP;
  p->mat[4]['E'-'A'] = COUP;
  
  return p;
}

/* Renvoi la couleur inverse */
int couleur_adverse(int couleur){
    if(couleur == NOIR){
        return BLANC;
    }
    return NOIR;
}


/* Renvoi le nombre de coups possibles */
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

/* Liste les coups possible sur le terminal */
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

/* Modifie le plateau pour enlever tout les coup possibles */
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

    /* on recupere une valeur en fonction du bout recherche RET permettra de de definir les bornes ou COOUP les coups possibles */
    if (bout == VIDE){
        tag = COUP;
    } else {
        tag = RET;
    }

    /* on parcours les cellules du plateau jusqu'arriver soit en dehors du plateau soit sur le "bout" */
    while (i >= 0 && i < p->n && j >= 0 && j < p->n
           && p->mat[i][j] == coul_adv){
        i += dir_x;
        j += dir_y;
    }
    
    /* si on est arrive sur notre bout on peut alors attribuer le tag a ce dernier */
    if (i >= 0 && i < p->n && j >= 0 && j < p->n
        && p->mat[i][j] == bout){
        p->mat[i][j] = tag;      
    }

    return p;
    
}

/* Regarde toute les cases adjcentes (et en diagonale) à la celulle c_depart et appel suite() si la condition est validee */
plateau *voisins(plateau *p, cellule c_depart, int coul_j, int bout){

    int i, j, coul_adv;

    for (i = -1; i <= 1; i++){
        for (j = -1; j <= 1; j++){
            if (c_depart.x+i >= 0 && c_depart.x+i < p->n && c_depart.y+j >= 0 && c_depart.y+j < p->n /* on évite le seg fault */
                && p->mat[c_depart.x+i][c_depart.y+j] == (coul_adv = couleur_adverse(coul_j))){
                suite(p, c_depart, coul_adv, i, j, bout);   
            }
        }
    }
    return p;
}

/* Permet d'identifier les coups possibles pour un joueur donne */
plateau *coups_possibles(plateau *p, int coul_j){

    cellule c;
    int i, j;

    /* on regarde chaque case du plateau jusqu'à trouver un pion du joueur */
    for (i=0; i < p->n; i++){
        for (j=0; j < p->n; j++){

            if (p->mat[i][j] == coul_j){ /* la cases contient un pion du joueur actuel */
                c.x = i;
                c.y = j;
                voisins(p, c, coul_j, VIDE); /* test de la presence de pions à retourner de voisin qui regardera ensuite les suites */
            }         
        }
    }

    return p;        
}

/* choisi un coup aleatoire parmis les coups disponibles */
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
    
    return coup;
}

/* renvoi la liste des "bornes" qui serviront ensuite avec le coup pour faire des actions sur les cellules qui se situent entre */
l_cellule bornes_pieces_a_retourner(plateau *p, cellule coup){

  int i, j, coul_j;
  l_cellule bornes;

  /* initialisation */
  coul_j = p->mat[coup.x][coup.y];
  bornes = creer_l_cellule();
  
  /* calcul des bornes pour le coup */
  voisins(p, coup, coul_j, coul_j);

  /* recuperation des cases possibles */
  for(i=0; i < p->n; i++){
    for(j=0; j < p->n; j++){

      if(p->mat[i][j] == RET){
	    bornes = ajouter_cellule(bornes, i, j);
        p->mat[i][j] = coul_j;
      }
    }
  }

  return bornes;
}

/* retourne les pieces entre le coup et les bornes dans la couleur passee en parametre*/
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


/* appelee en fin de partie, permet de definir le gagnant ou si'l y a egalite */
int couleur_gagnante(plateau *p){
    int i, j, noir = 0, blanc = 0;

    /* on compte les pions de chaque joueurs */
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

    /* retour de la valeur du gagnant*/
    if (blanc > noir){
        return BLANC;
    }

    if (noir > blanc){
        return NOIR;
    }
    
    /* sinon egalite */
    return 0;  
}

/* renvoi le score du joueur blanc */
int score_blanc(plateau *p){
    int i, j, acc = 0;

    for(i = 0; i < p->n; i++){
        for(j = 0; j < p->n; j++){
            if(p->mat[i][j] == BLANC){
                acc++;
            }
        }
    }
    return acc;
}

/* renvoi le score du joueur noir */
int score_noir(plateau *p){
    int i, j, acc = 0;

    for(i = 0; i < p->n; i++){
        for(j = 0; j < p->n; j++){
            if(p->mat[i][j] == NOIR){
                acc++;
            }
        }
    }
    return acc;
}
               
#endif
