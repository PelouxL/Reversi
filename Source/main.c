#include "main.h"
#include "time.h"

int main(){
  int n = 8;
  plateau *p = NULL;
  
  srand(time(NULL));
 
  p = initialisation_plateau(n);

  jeu_terminal(p);
  vider_plateau(p);
    
  exit(EXIT_SUCCESS);
}
