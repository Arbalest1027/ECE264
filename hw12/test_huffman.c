#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"

void destory_fn(void*);
static void int_print(const void*);

static int cmp(const void* p1, const void* p2){
	return *((const int*)p1) - (*(const int*)p2);
}

int main(int argc, char** argv) {
  int array[] = {1872,4,82,1236,48,77};
  Node* pq = NULL;
  Node* head = NULL;
  for (int i = 0;i < sizeof(array)/sizeof(array[0]);i++){
    pq_enqueue(&head,array + i,&cmp);
  }
  print_node(head,int_print);
  for (int i = 0;i < sizeof(array)/sizeof(array[0]);i++){
    stack_push(&pq,array+i);
  }
  print_node(pq,int_print);
  Node* lastnode = remove_last_node(&pq);
  print_node(lastnode,int_print);
  Node* first = pq_dequeue(&pq);
  print_node(first,int_print);
  destroy_node(pq,destory_fn);
  destroy_node(head,destory_fn);  

  destroy_node(lastnode,destory_fn);
  destroy_node(first,destory_fn);
  return EXIT_SUCCESS;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
void destory_fn(void* header){
  return;
}
static void int_print(const void* ptr) {
   printf("%d", *(const int*)ptr);
}

