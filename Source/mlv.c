#ifndef _MLV_C_
#define _MLV_C_

#include "mlv.h"
#include"jeu.h"

#define CASES 60
#define ESPACEMENT 0 /* ça me servait pour faire un espace entres les cases. Ici y'a pas d'espace mais je le garde pour la suite si on a besoin, on aura juste a modifier le nombre */
#define CONTOUR 35
#define TEXT 50 /* ça correspondra à l'espace entre le plateau et le texte */

int verif(bouton bouton, int coord_x, int coord_y){
    if((coord_x > bouton.x && coord_x < bouton.x + bouton.largeur) && (coord_y > bouton.y && coord_y < bouton.y + bouton.hauteur)){
        return 1;
    }
    return 0;
}

int clic_bouton(bouton bout[], int lng) {
    int s_x, s_y, i;
    
    MLV_wait_mouse(&s_x, &s_y);
    for (i = 0; i < lng; i++) {
        if (verif(bout[i], s_x, s_y) == 1) {
            return i;
        }
    }
    return i;
}

void cree_bouton(bouton *bouton, char *message, int x, int y, MLV_Font *police){
    int largeur, hauteur;
    MLV_get_size_of_adapted_text_box_with_font(message, police, 10, &largeur, &hauteur);
    bouton -> x = x - largeur/2 + 1;
    bouton -> y = y;
    bouton -> hauteur = hauteur;
    bouton -> largeur = largeur;
    strcpy(bouton -> txt, message);    
}

void afficher_text(bouton bouton, MLV_Font *police){
    MLV_draw_adapted_text_box_with_font(bouton.x, bouton.y, bouton.txt, police, 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_WHITE, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);
}

void affichage_mlv(plateau *p){
    int i, j, x, y, l_p, h_p, radius, base, contour_x, contour_y, taille_contour, text_x, text_y;
    char *text_l[] = {"A", "B", "C", "D", "E", "F", "G", "H"};
    MLV_Font *police;

    police = MLV_load_font("Letters for Learners.ttf", 30);

    MLV_clear_window(MLV_rgba(2, 9, 2, 255));

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
    MLV_draw_filled_rectangle(contour_x, contour_y, taille_contour, taille_contour, MLV_rgba(50, 35, 19, 250));

    /* affichage de toutes les cases */
    for(i = 0; i < p -> n; i++){
        for(j = 0; j < p -> n; j++){
            x = l_p + j * (CASES + ESPACEMENT);
            y = h_p + i * (CASES + ESPACEMENT);
            radius = 25;

            /* couleur cases */
            MLV_draw_filled_rectangle(x, y, CASES, CASES, MLV_rgba(26, 126, 26, 250));
            
            /* couleur contour cases */
            MLV_draw_rectangle(x, y, CASES, CASES, MLV_rgba(155, 155, 155, 255));

            /* affichage des pions */
            if(p -> mat[i][j] == 1){
                MLV_draw_filled_circle(x + CASES / 2, y + CASES / 2, radius, MLV_COLOR_BLACK);            }
            else if(p -> mat[i][j] == 2){
                MLV_draw_filled_circle(x + CASES / 2, y + CASES / 2, radius, MLV_COLOR_WHITE);
            }
            else if(p -> mat[i][j] == 10){
                MLV_draw_filled_circle(x + CASES / 2, y + CASES / 2, radius / 2, MLV_rgba(155, 155, 155, 150));
            }                
        }
    }

    /* affichage texte : 1 - 8 */
    for(i = 0; i < p -> n; i++){
        text_x = l_p - TEXT - CONTOUR - 5;
        text_y = h_p + i * (CASES + ESPACEMENT) + (CONTOUR / 2) - 5;
        MLV_draw_adapted_text_box_with_font(text_x, text_y, "%d", police, 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_WHITE, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER, i + 1);
    }

    /* affichage texte : A - H */
    for(i = 0; i < p -> n; i++){
        text_x = l_p + i * (CASES + ESPACEMENT) + (CONTOUR / 2);
        text_y = h_p + base + TEXT;
        MLV_draw_adapted_text_box_with_font(text_x, text_y, text_l[i], police, 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_WHITE, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER, i + 1);
    }
    
    MLV_actualise_window();
}

void affiche_cellule_possible_mlv(char *message, int text_x, int text_y){
    int text_w, text_h;

    MLV_get_size_of_adapted_text_box(message, 10, &text_w, &text_h);

    MLV_draw_adapted_text_box(text_x, text_y, message, 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_WHITE, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);

}

cellule obtenir_coord(plateau *p){
    int x, y, l_p, h_p, base, s_x, s_y;
    cellule c;

    MLV_wait_mouse(&s_x, &s_y);
    
    base = p -> n * (CASES + ESPACEMENT);
    l_p = (LX - base) / 2;
    h_p = (LY - base) / 2;

    if(s_x >= l_p && s_x <= l_p + base && s_y >= h_p && s_y <= h_p + base){
        x = (s_x - l_p) / (CASES + ESPACEMENT);
        y = (s_y - h_p) / (CASES + ESPACEMENT);
        printf("x = %d, y = %d\n", x, y);
        c.x = y;
        c.y = x;
        printf("Coordonnée dans le plateau cliqué : [%c ; %d]\n", c.x + 'A', y + 1);
    }
    else{
        c.x = -1;
        c.y = -1;
    }
    return c;
}

void afficher_coup_mlv(plateau *p){
    int i, j, x, y;
    char coup_p[50];
    
    x = 10;
    y = LY / 3;
    for(i = 0; i < p -> n; i++){
        for(j = 0; j < p -> n; j++){
            if(p -> mat[i][j] == COUP){
                sprintf(coup_p, "\n%c%d ", j +'A', i + 1);
                affiche_cellule_possible_mlv(coup_p, x, y);
                x += 30;
            }
        }
    }
    MLV_actualise_window();
}

plateau *demande_premier_joueur(bouton bouton[], plateau *p){
    int text_width, text_height, x, i, pressed;
    char *nom_bouton[] = {"BLANC", "NOIR"};

    MLV_Font *police;

    MLV_clear_window(MLV_rgba(2, 9, 2, 255));

    police = MLV_load_font("Letters for Learners.ttf", 100);

    MLV_get_size_of_adapted_text_box_with_font("Choisissez votre couleur de pion", police, 10, &text_width, &text_height);
    MLV_draw_adapted_text_box_with_font( (LX - text_width) / 2, 50, "Choisissez votre couleur de pion", police, 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_WHITE, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);

    x = 0;
    for(i = 0; i < 2; i++){
        cree_bouton(&bouton[i], nom_bouton[i], LX / 2 + x - 250, LY / 2, police);
        afficher_text(bouton[i], police);
        x += 250 * 2;
    }    MLV_actualise_window();
    
    pressed = clic_bouton(bouton, 4);
    printf("pressed = %d\n", pressed);
    
    if(pressed == 0){
        printf("NOIR\n");
        p -> j_couleur = NOIR;
    }
    else if(pressed == 1){
        printf("BLANC\n");
        p -> j_couleur = BLANC;
    }
    p->ordi_couleur = couleur_adverse( p->j_couleur );
    
    return p;
}

#endif
