#include "tree.h"
#include "list_node.h"
#include "frequency.h"

#ifndef MAIN_FUNC

int main(int argc, char **argv){
  if (argc != 2){
    printf("Wrong arguments\n");
    return EXIT_FAILURE;
  }
  // Create CharFreq array
  CharFreq * freq = malloc(sizeof(CharFreq) * NUMLETTER);
  // initialize all the frequencies inside freq array to be 0
  for (int i = 0; i < NUMLETTER; i++){
    freq[i].freq = 0;
  }
  // count frequency by calling CountFrequency function and passing the input filename
  int check = CountFrequency(argv[1],freq);
  if (check == 0){
    free(freq);
    return EXIT_FAILURE;
  }
  // sort frequencies by calling SortFrequency function
  SortFrequency(freq);
  // build linked list sorted linked list
  ListNode * list_head = ListBuild(freq);
  // Get two minimum frequencies and merge them and reduce one list node - call BuildHuffmanTree.
  list_head = BuildHuffmanTree(list_head);
  // Print the final huffman tree in prefix by calling the print function - call the prefix print function
  PrefixTreePrint(list_head -> treeNodePtr,0);
  // Free all the memory allocated
  CleanTree(list_head -> treeNodePtr);
  CleanList(list_head);
  free(freq);
  return EXIT_SUCCESS;
}
#endif
