#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"

Node* node_constr(void *);

Node *pq_enqueue(Node **pq, const void *new_object, 
                  int (*cmp_fn)(const void *, const void *))
{
  	if (new_object == NULL){
		return NULL;
	}
	if (*pq == NULL){
	  return stack_push(pq,new_object);
	}
	if (cmp_fn((*pq)->ptr,new_object) > 0){
	  return stack_push(pq,new_object);
    }
    return(pq_enqueue(&(*pq)->next,new_object,cmp_fn));
}

                       
Node *pq_dequeue(Node **pq)
{
  Node* list = *pq;
 // Node* add = malloc(sizeof(Node));
  *pq = (*pq)->next;
  list->next = NULL; 
  return list;
}


Node *stack_push(Node **stack, const void *new_object)
{
	Node* new_node = malloc(sizeof(Node));
	new_node->ptr = (void*)new_object;
	new_node->next = *stack;
	*stack = new_node;
	return new_node;
}

Node *stack_pop(Node **stack){
  Node* new_node = *stack;
//  Node* temp = malloc(sizeof(Node));
  *stack = (*stack)->next;
  new_node->next = NULL;
  return new_node;
}

Node *remove_last_node(Node **list){
  Node* end = *list;
  Node* nex = NULL;
  while (end->next != NULL){
    nex = end;
    end = end->next;
  }
  nex->next = NULL;
  return end;
}



void destroy_node(Node *list,void (*destory_fn)(void *)){
  if (list == NULL){
    return;
  }
   Node* curr = NULL;
  while (list != NULL){
    curr = list->next;
    destory_fn(list->ptr);
    free(list);
    list = curr;
  }
  list = NULL;
}
/* print an entire linked list                                           */
/* pq is the address of the first Node in the linked list               */
/* print_fn is the address of the function to print the generic object,  */
/* of which the address is stored in the ptr field of an Node in the    */
/* linked list                                                           */
/*                                                                       */
/* DO NOT CHANGE THIS FUNCTION, OTHERWISE YOUR OUTPUT WILL BE DIFFERENT  */
/* AND YOU WILL NOT RECEIVE CREDIT                                       */
 
void print_node(const Node *list, void (*print_fn)(const void *))
{
   while (list != NULL) {
      // print the memory associated with list->ptr
      print_fn(list->ptr);
      // print an arrow
      fprintf(stdout, "->");
      list = list->next;
   } 
   // print NULL and a newline after that 
   fprintf(stdout, "NULL\n");
}


