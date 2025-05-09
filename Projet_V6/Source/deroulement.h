#ifndef _DEROULEMENT_H_
#define _DEROULEMENT_H_

#include "plateau.h"

/* Lancement de la version terminal */
int jeu_terminal(plateau *p, int prof, int bot_vs_bot);

/* Lancement de la version graphique */
void jeu_mlv(plateau *p, int prof, int bot_vs_bot);

#endif
