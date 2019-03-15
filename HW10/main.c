#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pe10.h"


int main(int argc, char **argv) {
  bool * arr = malloc(sizeof(bool) * atoi(argv[1]));
  for (int i = 0; i < atoi(argv[1]);i++){
    arr[i] = true;
  }
  josephus(arr,atoi(argv[1]),atoi(argv[2]),atoi(argv[3]));
  free(arr);
  return EXIT_SUCCESS;
}
