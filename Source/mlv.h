#ifndef _MLV_H_
#define _MLV_H_

#include"plateau.h"
#include"cellule.h"

#define LX 1280
#define LY 720

void affichage_mlv(plateau *p);

cellule obtenir_coord(plateau *p, int s_x, int s_y);

#endif