#ifndef _IA_H_
#define _IA_H_

#include <stdlib.h>
#include <stdio.h>

typedef struct noeud{
    plateau *position;
    int nb_fils;
    struct noeud **fils;
}noeud;

typedef noeud *arbre;


#endif