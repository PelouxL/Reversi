#ifndef _MLV_C_
#define _MLV_C_

#include "mlv.h"
#include"jeu.h"

#define CASES 60 /* Taille cases */
#define ESPACEMENT 0 /* Espace entre les cases */
#define CONTOUR 35 /* Taille contour */
#define TEXT 50 /* Espace entre le plateau et le texte */


/* Fonction qui verifie si le clic de la souris est dans le bouton */
int verif(bouton bouton, int coord_x, int coord_y){
    if((coord_x > bouton.x && coord_x < bouton.x + bouton.largeur) && (coord_y > bouton.y && coord_y < bouton.y + bouton.hauteur)){
        return 1;
    }
    return 0;
}

/* Fonction qui verifie si le clic de la souris est dans un des boutons et retour la valeur */
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

/* Fonction qui cree un bouton */
void cree_bouton(bouton *bouton, char *message, int x, int y, MLV_Font *police){
    int largeur, hauteur;
    MLV_get_size_of_adapted_text_box_with_font(message, police, 10, &largeur, &hauteur);
    bouton -> x = x - largeur/2 + 1;
    bouton -> y = y;
    bouton -> hauteur = hauteur;
    bouton -> largeur = largeur;
    strcpy(bouton -> txt, message);    
}

/* Fonction qui affiche le texte du bouton */
void afficher_text(bouton bouton, MLV_Font *police){
    MLV_draw_adapted_text_box_with_font(bouton.x, bouton.y, bouton.txt, police, 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_WHITE, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);
}


/* Fonction qui affiche le plateau de jeu */
void affichage_mlv(plateau *p, int tour, int couleur){
    int i, j, x, y, l_p, h_p, radius, base, contour_x, contour_y, taille_contour, text_x, text_y;
    char *text_l[] = {"A", "B", "C", "D", "E", "F", "G", "H"};
    char text[100];
    MLV_Font *police;

    police = MLV_load_font("./Fonts/Letters for Learners.ttf", 30);
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
            if(p -> mat[i][j] == NOIR){
                MLV_draw_filled_circle(x + CASES / 2, y + CASES / 2, radius, MLV_COLOR_BLACK);            
            }
            else if(p -> mat[i][j] == BLANC){
                MLV_draw_filled_circle(x + CASES / 2, y + CASES / 2, radius, MLV_COLOR_WHITE);
            }
            else if(p -> mat[i][j] == 10 && couleur == tour){ 
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

    /* affichage du score en direct */
    police = MLV_load_font("./Fonts/Letters for Learners.ttf", 50);
    sprintf(text, "Blanc : %d --------------- Noir : %d", score_blanc(p), score_noir(p));
    MLV_get_size_of_adapted_text_box_with_font(text, police, 10, &text_x, &text_y);
    MLV_draw_adapted_text_box_with_font((LX - text_x) / 2, 5, text, police, 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_WHITE, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);   

    
    MLV_actualise_window();
}

/* Fonction qui récupère les coordonnées d'un clic */
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
        c.x = y;
        c.y = x;
    }
    else{
        c.x = -1;
        c.y = -1;
    }
    return c;
}

/* Fonction qui permet de choisir la couleur voulue */
plateau *demande_premier_joueur(bouton bouton[], plateau *p){
    int text_width, text_height, x, i, pressed;
    char *nom_bouton[] = {"BLANC", "NOIR"};

    MLV_Font *police;

    MLV_clear_window(MLV_rgba(2, 9, 2, 255));

    police = MLV_load_font("./Fonts/Letters for Learners.ttf", 100);

    MLV_get_size_of_adapted_text_box_with_font("Choisissez votre couleur de pion", police, 10, &text_width, &text_height);
    MLV_draw_adapted_text_box_with_font( (LX - text_width) / 2, 50, "Choisissez votre couleur de pion", police, 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_WHITE, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);

    x = 0;
    for(i = 0; i < 2; i++){
        cree_bouton(&bouton[i], nom_bouton[i], LX / 2 + x - 250, LY / 2, police);
        afficher_text(bouton[i], police);
        x += 250 * 2;
    }    MLV_actualise_window();
    
    pressed = clic_bouton(bouton, 4);
    
    if(pressed == 0){
        p -> j_couleur = BLANC;
    }
    else if(pressed == 1){
        p -> j_couleur = NOIR;
    }
    p->ordi_couleur = couleur_adverse( p->j_couleur );
    
    return p;
}

#endif
