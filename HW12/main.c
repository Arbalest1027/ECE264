#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pa12.h"




int main(int argc, char **argv)
{
  if (!strcmp(argv[1],"-J")){
    struct node * head;
    init(&head,atoi(argv[2]));
    josp(&head,atoi(argv[3]),atoi(argv[4]),atoi(argv[2]));
    struct node * temp;
    while (head != NULL){
      temp = head;
      head = head -> next;
      free(temp);
    }
  }
  if (!strcmp(argv[1],"-J2")){
    struct dnode * dhead;
    init2(&dhead,atoi(argv[2]));
    josp2(&dhead,atoi(argv[3]),atoi(argv[4]),atoi(argv[2]));
    struct dnode * temp;
    while (dhead != NULL){
      temp = dhead;
      dhead = dhead -> next;
      free(temp);
    }
  }
}
