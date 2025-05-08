#ifndef _IA_C_
#define _IA_C_

#include "ia.h"
#include "eval.h"
#include "joueur.h"

plateau *copie_plateau(plateau *p){

    int i, j;
    plateau *pc = NULL;

    pc = initialisation_plateau(p->n);

    pc->j_couleur = p->j_couleur;
    pc->ordi_couleur = p->ordi_couleur;

    for (i=0; i < p->n; i++){
        for (j=0; j < p->n; j++){
            pc->mat[i][j] = p->mat[i][j];
        }
    }

    return pc;
}

arbre creer_noeud(){
    arbre a = NULL;
    if( ( a = (arbre) malloc (sizeof(noeud))) == NULL){
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        exit(EXIT_FAILURE);
    }
    
    a->points = 0;
    a->profondeur = 0;
    a->coup.x = -1;
    a->coup.y = -1;
    a->descendance = NULL;
    a->suivant = NULL;
    
    return a;
}


arbre creer_arbre_aux(plateau *p, arbre a, int **tab_points, int prof, int i){
    arbre courant = NULL;
    int couleur;
    int k, j;
    plateau *p_copie = NULL;

    if (i > prof){
        return NULL;
    }
   

    /* on recupere la couleur */
    if (prof%2 == 1){
        couleur = p->ordi_couleur;
    } else {
        couleur = p->j_couleur;
    }
    

    /* ajouter les fils */
    for(j = 0; j < p->n; j++){
        for(k = 0; k < p->n; k++){
            if(p->mat[j][k] == COUP){

                p_copie = copie_plateau(p);

                /* le fils est ajoute a la descendance */
                a = ajouter_fils(a, tab_points, j, k, p_copie);

                

                /* on recupere le fils qu'on a ajoute */
                if (courant == NULL) {
                    courant = a->descendance;
                } else {
                    courant = courant->suivant;
                }

                /* on recupere les coups possible en veillant a enlever ceux du tour precedent */
                p_copie = remise_a_zero(p_copie);
                p_copie = coups_possibles(p_copie, couleur);

                /* calcul du poids */
                calcul_points(courant, a, tab_points, p_copie);

                /* on rappel creer_arbre_aux */
                
                creer_arbre_aux(p_copie, courant, tab_points, prof, i+1);

                /* free */
                free(p_copie);
                p_copie = NULL;
                
            }
        }
    }

    return a;
}

arbre creer_arbre(plateau *p, int **tab_points, int prof){
    arbre a;
    
    a = creer_noeud(p); /* racine */
    creer_arbre_aux(p, a, tab_points, prof, 1); 
    return a;
}


          

arbre ajouter_fils(arbre a, int **tab_points, int i, int j, plateau *p){
    arbre fils = NULL, courant = a->descendance;
    int couleur, poids;
    l_cellule bornes;
    
    /* on creer le fils avec une copie du plateau et une profondeur = a celle du pere + 1 */
    fils = creer_noeud();
    fils->profondeur = a->profondeur + 1;
    fils->coup.x = i;
    fils->coup.y = j;
    
    /* on recupere la couleur du joueur actuel */
    if (fils->profondeur % 2 == 1){
        couleur = p->ordi_couleur;
    } else {
        couleur = p->j_couleur;
    }

    /* on retourne les pieces et on recupere la liste des pieces retournée */
    p->mat[i][j] = couleur;
    
    bornes = bornes_pieces_a_retourner(p, fils->coup);
    fils->bornes = bornes;
    retourner_pieces(bornes, p, couleur, fils->coup);

    /* on calcule le poids total des pieces retournees 
       ET on ajoute/retire des points selon le joueur */

    poids = evaluation_position(tab_points, fils->bornes, fils->coup);   
    
    if (fils->profondeur % 2 == 1){
      fils->points =  a->points + poids;
    } else {
      fils->points =  a->points  - poids;
    }
        
    /* on ajoute fils a la descendance */
    if(a->descendance == NULL){
        a->descendance = fils;
    }else{
        while(courant->suivant != NULL){
            courant = courant->suivant;
        }
        courant->suivant = fils;
    }
    
    return a;
}

void calcul_points(arbre fils, arbre a, int **tab_points, plateau *p){
    int acc, pos, 
        poids = 0;

    /* points position */
    pos = evaluation_position(tab_points, fils->bornes, fils->coup);   
    poids += pos;

    /* points possibilités adverses */
    acc = reste_coup(p);
    acc *= 2;  

    poids += acc;

    /* points par rapport au père */
    if (fils->profondeur % 2 == 1){
        fils->points =  a->points + poids;
      } else {
        fils->points =  a->points  - poids;
    }
}


void affiche_arbre(arbre a){
    arbre courant = a->descendance;

    if (a == NULL){
        return;
    }
    printf("Points du plateau : %d\n", a->points);
        
    while (courant != NULL){
        affiche_arbre(courant);       
        courant = courant->suivant;
    }
    
}

void liberer_arbre(arbre a){
  arbre courant = a->descendance, suivant = NULL;

  if (a == NULL){
    return;
  }
  
  while( courant != NULL){
    suivant = courant->suivant;
    liberer_arbre(courant);
    courant = suivant;
  }
  
  free(a);
  a = NULL;
}



#endif
    

