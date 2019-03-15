#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "maze.h"

int find_path_from_top_entrance_to_bottom_exit(char *maze_file, char *directions_file, char *visited_file);

int main(int argc, char* argv[]) 
{
   if (argc < 2) 
   {
       return EXIT_FAILURE;
   }
   char* args1;
   char *args2;
   char* args3;
   char* args4;
   char* argm1;
   char* argm2;
   char* argm3;
   char* argm4;
    if (strcmp("-s",argv[1]) == 0 && argc == 9){
     Coord source = {
       .row = strtol(argv[5],&args1,10),
       .col = strtol(argv[6],&args2,10)
     };
     Coord destination = {
       .row = strtol(argv[7],&args3,10),
       .col = strtol(argv[8],&args4,10)
     };
     if (*args1 != '\0' || *args2 != '\0' || *args3 != '\0' || *args4 != '\0'){
       return EXIT_FAILURE;
     }
     int step_count = simulate_movement(argv[2],argv[3],argv[4],source,destination);
     printf("%d\n",step_count);
     }
   if (strcmp("-m",argv[1]) == 0 && argc == 8){

          Coord source2 = {
       .row = strtol(argv[4],&argm1,10),
       .col = strtol(argv[5],&argm2,10)     
     };
     Coord destination2 = {
       .row = strtol(argv[6],&argm3,10),
       .col = strtol(argv[7],&argm4,10)
     };
     if (*argm1 != '\0' || *argm2 != '\0' || *argm3 != '\0' || *argm4 != '\0'){
       return EXIT_FAILURE;
     }
     int step = dfs_shortest_path_directions(argv[2],argv[3],source2,destination2);
     printf("%d\n",step);
   }
   else {
      return EXIT_FAILURE;
      }
   return EXIT_SUCCESS;
}
