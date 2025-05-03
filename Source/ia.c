#ifndef _IA_C_
#define _IA_C_

#include "ia.h"

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

arbre creer_noeud(plateau *p){
    arbre a = NULL;

    if( ( a = (arbre) malloc (sizeof(noeud))) == NULL){
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        exit(EXIT_FAILURE);
    }
    
    a->p = copie_plateau(p);
    remise_a_zero(a->p);
    a->points = 0;
    a->profondeur = 0;
    a->coup.x = -1;
    a->coup.y = -1;
    a->descendance = NULL;
    a->suivant = NULL;
    
    return a;
}

/* fonction permettant de creer un arbre avec une profondeur donne */
arbre creer_arbre_aux(arbre a, int **tab_points, int prof, int i){
    arbre courant = NULL;

    if (i > prof){
        return NULL;
    }
    
    a = descendance(a, tab_points);
    courant = a->descendance;
    i += 1;
    
    while (courant != NULL){
        /* printf("profondeur = %d, i = %d\n", prof, i); */
      creer_arbre_aux(courant, tab_points, prof, i);
        courant = courant->suivant;
    }
    return a;
}

arbre creer_arbre(plateau *p, int **tab_points, int prof){
    arbre a;
    
    a = creer_noeud(p); /* racine */
    creer_arbre_aux(a, tab_points, prof, 1);

    return a;
}


arbre descendance(arbre a, int **tab_points){
    int i, j;
    
    if (a->profondeur % 2 == 0){
        coups_possibles(a->p, a->p->ordi_couleur);
    } else {
        coups_possibles(a->p, a->p->j_couleur);
    }
    
    for(i = 0; i < a->p->n; i++){
        for(j = 0; j < a->p->n; j++){
            if(a->p->mat[i][j] == COUP){

	      a = ajouter_fils(a, tab_points, i, j);
                /* printf("ajout du fils %d\n", acc++); */
                
            
            }
        }
    }
    return a;
}

cellule moyenne_arbre(arbre a){
    arbre courant = a->descendance;
    cellule c, c_tmp;

    c.x = 0;
    c.y = 0;
    
    if(a->descendance == NULL){
        c.x = a->points;
        c.y = 1;
    } else {
        
        while(courant != NULL){
            c_tmp = moyenne_arbre(courant);
            c.x += c_tmp.x;
            c.y += c_tmp.y;
            courant = courant->suivant;
        }
        
    }
    
    return c;
    
}
/*

plateau *eval(arbre a){
    arbre courant = a->descendance;
    cellule c;
    float moy, moy_tmp;
    plateau *p;
    
    c = moyenne_arbre(courant);
    moy = c.x/c.y;
    p = courant->p;
    courant = courant->suivant;
    
    /************************************/
    /* calcul du ratio perte/gain pions */
    /************************************/
    /*
    while(courant != NULL){
        c = moyenne_arbre(courant);
        moy_tmp = c.x/c.y;
        /* printf("voici la valeur de la moyenne de l'arabe %f, moy ac = %f\n", moy_tmp, moy);  
        if(moy_tmp > moy || (moy_tmp == moy && rand()%2 == 1)){
            moy = moy_tmp;
            p = courant->p;
        }       
        courant = courant->suivant;
    }

    return p;
}
    */
          
void affiche_arbre(arbre a){
    arbre courant = a->descendance;

    if (a == NULL){
        return;
    }
    printf("Points du plateau : %d\n", a->points);
    affiche_plateau(a->p);
    
    /* printf("Score : %d\n", a->points); */
        
    while (courant != NULL){
        affiche_arbre(courant);       
        courant = courant->suivant;
    }
    
}

arbre ajouter_fils(arbre a, int **tab_points, int i, int j){
    arbre fils = NULL, courant = a->descendance;
    cellule c;
    int couleur;
    
    /* on creer le fils avec une copie du plateau et une profondeur = a celle du pere + 1 */
    fils = creer_noeud(a->p);
    fils->profondeur = a->profondeur + 1;

    fils->coup.x = i;
    fils->coup.y = j;
    
    /* mettre couleur du joueur actuel ) */
    if (fils->profondeur % 2 == 1){
        couleur = fils->p->ordi_couleur;
    } else {
        couleur = fils->p->j_couleur;
    }
    fils->p->mat[i][j] = couleur;

    /* on retourne les pieces ET on recupere les points */
    c.x = i;
    c.y = j;
    
    if (fils->profondeur % 2 == 1){
      fils->points =  a->points + retourner_pieces(fils->p, tab_points, c);
    } else {
      fils->points =  a->points - retourner_pieces(fils->p, tab_points, c);
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
    

