#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pa08.h"


int main(int argc, char *argv[]) {
  if (!strcmp(argv[1],"-D")){
    DoubleVar * var = malloc(sizeof(DoubleVar));
    var -> digit_start = atoi(argv[2]) + 48;
    var -> digit_end = atoi(argv[3]) + 48;
    int len = atoi(argv[4]);
    for (int i = 3;i <= len; i++){
      char * str = malloc(sizeof(char) * i);
      createDouble(str,var,0,false,i);
      free(str);
    }
    free(var);
  }
  else if (!strcmp(argv[1],"-VID")){
    VIDVar * Ivar = malloc(sizeof(VIDVar));
    Ivar -> lower_case_start = argv[2][0];
    Ivar -> lower_case_end = argv[3][0];
    Ivar -> upper_case_start = argv[4][0];
    Ivar -> upper_case_end = argv[5][0];
    Ivar -> digit_start = atoi(argv[6]) + 48;
    Ivar -> digit_end = atoi(argv[7]) + 48;
    int len = atoi(argv[8]);
    for (int i = 1;i <= len; i++){
      char * str = malloc(sizeof(char) * i);
      createVID(str,Ivar,0,i);
      free(str);
    }
    free(Ivar);
  }
	return EXIT_SUCCESS;
}
