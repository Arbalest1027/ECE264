#include "pa15.h"
 
#ifndef MAIN_FUNC


//Main function:
//1. if the arguments != 4 then print "Wrong arguments\n" and return EXIT_FAILURE
//2. 1st input is long value using random seed needed for the generating the binary search tree
//3. 2nd input is long values - which is number of nodes for the binary search tree
//4. If the random seed or number of nodes input is wrong - Print "Wrong inputs\n" and return EXIT_FAILURE
//5. Call CreateBinarySearchTree function to get the tree
//6. If tree is not generated and you get NULL from it, then print "Binary Create Failed \n" and return EXIT_FAILURE
//7. 3rd input is output filename, in which output needs to be printed
//8. if file read fails, free memory and return EXIT_FAILURE


int main(int argc, char **argv){
  if (argc != 4){
    printf("Wrong arguments\n");
    return EXIT_FAILURE;
  }
  long seed = strtol(argv[1],NULL,10);
  long num = strtol(argv[2],NULL,10);
  TreeNode * tn = CreateBinarySearchTree(seed,num);
  if (tn == NULL){
    printf("Binary Create Failed\n");
    return EXIT_FAILURE;
  }
  int check = CreateBinaryFromTree(tn,argv[3]);
  if (check == 1){
      CleanTree(tn);
    return EXIT_FAILURE;
  }
  CleanTree(tn);
  return EXIT_SUCCESS;

}
#endif
