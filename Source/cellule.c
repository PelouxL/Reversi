#ifndef _CELLULE_C_
#define _CELLULE_C_

#include "cellule.h"

/* si la l_cellule est vide alors renvoie 0*/
int est_l_c_vide(l_cellule l_c){
    if(l_c.n == 0 && l_c.cel == NULL){
        return 1;
    }
    return 0;
}

/* affiche toutes les cellules contenue dans l_cellule */
void afficher_cel(l_cellule l_c){
    
    int i;
    for( i = 0; i < l_c.n ; i++ ){
        printf("%d%c ", l_c.cel[i].x+1, l_c.cel[i].y + 'A');
    }
    printf("\n");
}

/* creer une l_cellule et la retourne */
l_cellule creer_l_cellule(){ 
    l_cellule  l_c;
    l_c.n = 0;
    l_c.cel = NULL;
    return l_c;
}

/* fait une reallocation ou alloue(si lc n'est pas encore en mémoire) mémoire sur la l_cellule et vérifie si on ajoute pas un doublon*/
l_cellule ajouter_cellule(l_cellule l_c, int x, int y){
  cellule c;
  c.x = x;
  c.y = y;
  /* verifie si l'element existe deja dans l_c*/
  if(appartient_l_c(l_c, c)){
    printf("Attention doublons, liste inchangée\n");  
    return l_c;
  }
  
  l_c.n++;
  if(l_c.cel != NULL){
    if ((l_c.cel = (cellule *) realloc(l_c.cel, l_c.n * sizeof(cellule))) == NULL){
      fprintf(stderr,"Erreur de reallocation memoire l_cellule\n");
      exit(EXIT_FAILURE);
    }
    
  }else{
    
    if ((l_c.cel = (cellule *) malloc(l_c.n * sizeof(cellule))) == NULL){
      fprintf(stderr,"Erreur de allocation memoire l_cellule\n");
      exit(EXIT_FAILURE);
    }
  }
  
  l_c.cel[l_c.n-1].x = x;
  l_c.cel[l_c.n-1].y = y;

  return l_c;
}



/* prend deux l_cellule et les concatene ( vérifie a ne pas ajouter de doublons) */
l_cellule concat_l_cellule(l_cellule l_c1, l_cellule l_c2){
    int i, j, ajout;

    if(l_c1.n == 0){
        return l_c2;
    }
    
    for(i = 0; i < l_c2.n; i++){
    
        ajout = 1;
        
        for(j = 0; j < l_c1.n; j++){
                
            if(l_c2.cel[i].x == l_c1.cel[j].x && l_c2.cel[i].y == l_c1.cel[j].y){
                ajout = 0;
            }
        }
        
        if(ajout == 1){
            l_c1 = ajouter_cellule(l_c1, l_c2.cel[i].x, l_c2.cel[i].y);
        }
        
    }

    liberer_l_cellule(&l_c2);
    
    return l_c1;
}
/* libère en mémoire la l_cellule */
void liberer_l_cellule(l_cellule *l_c){
    free(l_c->cel);
    l_c->cel = NULL;
}

/* supprime un element cellule coup de la l_cellule*/
l_cellule *supprimer_cellule(l_cellule *l_c, cellule coup){

    int i, supp = 0;
    /* on recher l'élement asupprimer */
    for(i = 0; i < l_c->n; i++){
        
        if(l_c->cel[i].x == coup.x && l_c->cel[i].y == coup.y){
            supp = 1;
        }

        if (supp == 1 && (i+1) < l_c->n){
            l_c->cel[i] = l_c->cel[i + 1];
        }
    }

    /* reallocation ou liberation */
    if (l_c->n > 0){
        if((l_c->cel = (cellule *) realloc (l_c->cel, l_c->n*sizeof(cellule))) == NULL){
            fprintf(stderr, "Erreur lors de la suppression\n");
            exit(EXIT_FAILURE);
        }
    } else {
        liberer_l_cellule(l_c);
        printf("liberation effectuer\n");
    }
    
    return l_c;
}
/* verifie et renvoie 1 si une cellule appartiens a une l_cellule sinon 0*/
int appartient_l_c(l_cellule l_c, cellule c){
    int i;
    
    for(i = 0; i < l_c.n; i++){
        if(c.x == l_c.cel[i].x && c.y  == l_c.cel[i].y){
            return 1;
        }
    }
    return 0;
}


#endif
