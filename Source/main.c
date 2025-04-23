#include "main.h"
#include "time.h"

int main(){
  int n = 8;
  plateau *p = NULL;
  
  srand(time(NULL));
 
  p = initialisation_plateau(n);

  /* MLV_create_window("Reversi", "Reversi", LX, LY); */
  jeu_terminal(p);
  /* jeu_mlv(p); */
  vider_plateau(p);
    
  exit(EXIT_SUCCESS);
}
