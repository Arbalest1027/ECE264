#include <stdio.h>
#include <stdlib.h>
#include "pa12.h"

#ifndef INIT
//head: the head of the singly linkedlist.
//length: the length of the singly linkedlist.
//This function will create and initialize the singly linkedlist with length=length, 
//The values of the nodes within the singly linkedlist will be the same as array indices.
//For example, if the singly linkedlist length is 4, the values of the nodes will be 0 1 2 3
void init(struct node **head,int length)
{
    *head = malloc(sizeof(nodeType));
    struct node* cur = *head;
    for (int i = 0; i < length; i++) {
        cur->value = i;
        cur->next = (i < (length - 1)) ? malloc(sizeof(nodeType)) : NULL;
        cur = cur->next;
    }	

}
#endif

#ifndef PRINT
//head: the head of the singly linkedlist.
//This function will print the values of the nodes within the singly linkedlist.
//For example, if the values of the nodes within the singly linkedlist are 1 5 6 8 9 10, this function will print 1,5,6,8,9,10
//Note: there is no extra comma nor at the beginning nor at the end.
void print(struct node **head)
{
  struct node * temp = *head;
  if (temp == NULL){
    printf("\n");
    return;
  }
  while(temp -> next != NULL){
    printf("%d,",temp -> value);
    temp = temp -> next;
  }
  printf("%d\n",temp -> value);

}
#endif

#ifndef JOSPI
//head: the head of the singly linkedlist.
//k : this variable will be used for counting if count = k, the element will be out.
//p : this variable will be used for printing if the number of remaining elements/nodes is divisible by p (call the print function).
//length: the length of the singly linkedlist.
//This function will solve the josephus problem using the singly linkedlist.
void josp(struct node ** head,int k,int p,int length)
{
    int remain = length;
    int count = 0;
    struct node * temp = *head;
    struct node * prev = *head;
    while (remain > 1){
      count = 0;
      while (count != k){
	if (temp -> next == NULL){
	  temp = *head;
	  prev = *head;
	  count++;
	}
	else {
	  prev = temp;
	  temp = temp -> next;
	  count++;
	}
      }
      if (temp -> next == NULL){
	free(temp);
	prev -> next = NULL;
	temp = *head;
	remain--;
      }
      else if (temp == (*head)){
	*head = (*head) -> next;
	free(temp);
	temp = (*head);
	remain--;
      }
      else {
	prev -> next = temp -> next;
	temp -> next = temp -> next -> next;
	free(temp);
	temp = prev -> next;
	remain--;
      }
      if (remain % p == 0){
	print(head);
      }
    }
}
#endif


#ifndef INITII
//head: the head of the doubly linkedlist.
//length: the length of the doubly linkedlist.
//This function will create and initialize the doubly linkedlist with length=length, 
//The values of the nodes within the doubly linkedlist will be the same as array indices.
//For example, if the doubly linkedlist length is 4, the values of the nodes will be 0 1 2 3
//NOTE: this is a doubly linkedlist you should assign the prev pointer for each node probably.
//NOTE: head->prev is NULL as well as tail->next.

void init2(struct dnode ** head,int length)
{
    *head = malloc(sizeof(dnodeType));
    (*head) -> prev = NULL;
    struct dnode* cur = *head;
    struct dnode* prev = *head;
    for (int i = 0; i < length; i++) {
        cur -> value = i;
	cur -> prev = (i == 0)? NULL : prev;
        cur -> next = (i < (length - 1)) ? malloc(sizeof(dnodeType)) : NULL;
        cur = cur -> next;
	if (i != 0){
	  prev = prev -> next;
	}
    }	  
}
#endif


#ifndef PRINTII
//head: the head of the doubly linkedlist.
//This function will print the values of the nodes within the doubly linkedlist.
//For example, if the values of the nodes within the doubly linkedlist are 1 5 6 8 9 10, this function will print 1,5,6,8,9,10
//Note: there is no extra comma nor at the beginning nor at the end.
void print2(struct dnode ** head)
{
    struct dnode * temp = *head;
    if (temp == NULL){
      printf("\n");
      return;
    }
    while(temp -> next != NULL){
      printf("%d,",temp -> value);
      temp = temp -> next;
    }
    printf("%d\n",temp -> value);
}

#endif


#ifndef JOSPII
//head: the head of the doubly linkedlist.
//k : this variable will be used for counting if count = k, the element will be out.
//q : this variable will be used for flipping the direction. If while counting, the value of the node is divisible by q,
//you will take the node out, flip the direction, and continue counting.
//length: the length of the doubly linkedlist.
//This function will solve the modified josephus problem using the doubly linkedlist.
//NOTE: you should call the print2() function after any delete operation.
void josp2(struct dnode **head, int k, int q,int length)
{
    int remain = length;
    int count = 0;
    int direction = 1;
    struct dnode * temp = *head;
    struct dnode * last;
    struct dnode * temp2;
    while (temp -> next != NULL){
      temp = temp -> next;
    }
    last = temp;
    temp = *head;
    while (remain > 1){
      count = 0;
      while (count < k){
	if (count != 0 && (temp -> value) % q == 0){
	  direction = 1 - direction;
	  if (temp -> next == NULL){
	    temp -> prev -> next = NULL;
	    last = temp -> prev;
	    temp2 = temp -> prev;
	    free(temp);
	    if (direction == 1){
	      temp = *head;
	    }
	    else if(direction == 0){
	      temp = temp2;
	    }
	  }
	  else if (temp == (*head)){
	    *head = (*head) -> next;
	    (*head) -> prev = NULL;
	    free(temp);
	    if (direction == 1){
	      temp = (*head);
	    }
	    else if (direction == 0){
	      temp = last;
	    }
	  }
	  else {
	    if (direction == 1){
	      temp -> prev -> next = temp -> next;
	      temp -> next -> prev = temp -> prev;
	      temp2 = temp -> next;
	      free(temp);
	      temp = temp2;
	    }
	    else if (direction == 0){
	      temp -> next -> prev = temp -> prev;
	      temp -> prev -> next = temp -> next;
	      temp2 = temp -> prev;
	      free(temp);
	      temp = temp2;
	    }
	    //count++;
	  }
	  count++;
	  print2(head);
	  remain--;
	}
	if(count < k){
	  if (direction == 1){
	    if (temp -> next == NULL){
	      temp = *head;
	      count++;
	    }
	    else {
	      temp = temp -> next;
	      count++;
	    }
	}
	  else if (direction == 0){
	    if (temp -> prev == NULL){
	      temp = last;
	      count++;
	    }
	    else {
	      temp = temp -> prev;
	      count++;
	    }
	  }
	}
      }
      // deleting normally
      if (temp -> next == NULL){
	  temp -> prev -> next = NULL;
	  last = temp -> prev;
	  temp2 = temp -> prev;
	  if (temp -> value % q == 0){
	    direction = 1 - direction;
	  }
	  free(temp);
	  if (direction == 1){
	    temp = *head;
	  }
	  else if(direction == 0){
	    temp = temp2;
	  }
	  remain--;
      }
      else if (temp == (*head)){
	  *head = (*head) -> next;
	  (*head) -> prev = NULL;
	  if (temp -> value % q == 0){
	    direction = 1 - direction;
	  }
	  free(temp);
	  if (direction == 1){
	    temp = (*head);
	  }
	  else if (direction == 0){
	    temp = last;
	  }
	  remain--;
      }
      else {
	  temp -> prev -> next = temp -> next;
	  temp -> next -> prev = temp -> prev;
	  temp2 = temp -> next;
	  if (temp -> value % q == 0){
	    direction = 1 - direction;
	  }
	  free(temp);
	  if (direction == 1){
	    temp = temp2;
	  }
	  else if (direction == 0){
	    temp = temp2 -> prev;
	  }
	  remain--;
      }
      print2(head);
    }	
    
}

#endif




