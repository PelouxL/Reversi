#ifndef _MAIN_C_
#define _MAIN_C_

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include "main.h"
#include "time.h"

int main(int argc, char *argv[]){
    int opt, i;
    int bot_vs_bot = 0;
    int min_max = 0;
    char mode = 'g';
    int prof = 0;
    int n = 8;
    plateau *p = NULL;
    const char *optstring = "p:m:";

    const struct option lopts[] = {
        {"prof", required_argument, NULL, 'p'},
        {"mode", required_argument, NULL, 'm'},
        {"bot", no_argument, NULL, 'b'},
        {"min_max", no_argument, NULL, 'a'},
        {NULL, 0, NULL, 0}
    };
    
    srand(time(NULL));
    
    while ((opt = getopt_long_only(argc, argv, optstring, lopts, NULL)) != -1) {
        switch (opt) {
            case 'p':
                prof = atoi(optarg);
                break;
            case 'm':
                mode = optarg[0];
                break;
            case 'b':
                bot_vs_bot = 1;
                break;
            case 'a':
                min_max = 1;
                break;
        }
    }

    for (i = 1; i < argc; i++) {
        if (strncmp(argv[i], "-p", 2) == 0 || strncmp(argv[i], "-m", 2) == 0 || strncmp(argv[i], "-b", 2) == 0){
            fprintf(stderr, "Erreur : utilisez uniquement les options longues : --prof et --mode et --bot\n");
            exit(EXIT_FAILURE);
        }
    }
    
    if(prof == -1 || (mode != 't' && mode != 'g')){
        fprintf(stderr, "Usage : %s   --prof <profondeur souhaitée : au dessus de 2>\n   --mode <mode : t pour terminal ou g pour MLV>\n   --bot : si veut bot contre bot ou par défaut jouer\n   --min_max : Si on lance en min_max ou par défaut en alpha_beta\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if(prof < 2){
        fprintf(stderr, "Usage : %s   --prof <profondeur souhaitée : obligatoirement au dessus de 2>\n   --mode <mode : t pour terminal ou g pour MLV>\n   --bot : si veut bot contre bot ou par défaut jouer\n   --min_max : Si on lance en min_max ou par défaut en alpha_beta\n\n ", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    p = initialisation_plateau(n);

    if(mode == 't'){   
        jeu_terminal(p, prof, bot_vs_bot, min_max);
    }
    else{
        MLV_create_window("Reversi", "Reversi", LX, LY);
        jeu_mlv(p, prof, bot_vs_bot, min_max);
    }
    vider_plateau(p);
    
    exit(EXIT_SUCCESS);
}

#endif