#include "mlv.h"
#include <MLV/MLV_all.h>

#define CASES 60
#define ESPACEMENT 0 /* ça me servait pour faire un espace entres les cases. Ici y'a pas d'espace mais je le garde pour la suite si on a besoin, on aura juste a modifier le nombre */
#define CONTOUR 35
#define TEXT 50 /* ça correspondra à l'espace entre le plateau et le texte */

void affichage_mlv(plateau *p){
    int i, j, x, y, l_p, h_p, radius, base, contour_x, contour_y, taille_contour, text_x, text_y;
    char *text_l[] = {"A", "B", "C", "D", "E", "F", "G", "H"};

    /* taille plateau de jeu */
    base = p -> n * (CASES + ESPACEMENT);

    /* emplacement général du plateau */
    l_p = (LX - base) / 2;
    h_p = (LY - base) / 2;

    /* calcul pour contour */
    contour_x = l_p - CONTOUR;
    contour_y = h_p - CONTOUR;
    taille_contour = base + 2 * CONTOUR;

    /* dessin contour du plateau */
    MLV_draw_filled_rectangle(contour_x, contour_y, taille_contour, taille_contour, MLV_rgba(81, 60, 44, 250));

    /* affichage de toutes les cases */
    for(i = 0; i < p -> n; i++){
        for(j = 0; j < p -> n; j++){
            x = l_p + j * (CASES + ESPACEMENT);
            y = h_p + i * (CASES + ESPACEMENT);
            radius = 25;

            /* couleur cases */
            MLV_draw_filled_rectangle(x, y, CASES, CASES, MLV_rgba(77, 161, 103, 250));
            
            /* couleur contour cases */
            MLV_draw_rectangle(x, y, CASES, CASES, MLV_COLOR_GREY);

            /* affichage des pions */
            if(p -> mat[i][j] == 1){
                MLV_draw_filled_circle(x + CASES / 2, y + CASES / 2, radius, MLV_COLOR_BLACK);            }
            else if(p -> mat[i][j] == 2){
                MLV_draw_filled_circle(x + CASES / 2, y + CASES / 2, radius, MLV_COLOR_WHITE);
            }
        }
    }

    /* affichage texte : 1 - 8 */
    for(i = 0; i < p -> n; i++){
        text_x = l_p - TEXT - CONTOUR;
        text_y = h_p + i * (CASES + ESPACEMENT) + (CONTOUR / 2);
        MLV_draw_adapted_text_box(text_x, text_y, "%d", 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_WHITE, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER, i + 1);
    }

    /* affichage texte : A - H */
    for(i = 0; i < p -> n; i++){
        text_x = l_p + i * (CASES + ESPACEMENT) + (CONTOUR / 2);
        text_y = h_p + base + TEXT;
        MLV_draw_adapted_text_box(text_x, text_y, text_l[i], 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_WHITE, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER, i + 1);
    }
    
    MLV_actualise_window();
}

cellule obtenir_coord(plateau *p, int s_x, int s_y){
    int x, y, l_p, h_p, base;
    cellule c;
    
    base = p -> n * (CASES + ESPACEMENT);
    l_p = (LX - base) / 2;
    h_p = (LY - base) / 2;

    if(s_x >= l_p && s_x <= l_p + base && s_y >= h_p && s_y <= h_p + base){
        x = (s_x - l_p) / (CASES + ESPACEMENT);
        y = (s_y - h_p) / (CASES + ESPACEMENT);
        printf("Coordonnée dans le plateau cliqué : [%d ; %d]\n", x, y);
        c.x = x;
        c.y = y;
    }
    else{
        printf("Valeur cliqué pas dans le plateau\n");
    }
    return c;
}