#include <stdio.h>
#include <stdlib.h>
#include "pe11.h"

#ifndef PRINT
void print(struct node** head)
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

#ifndef INSF
void insertFirst(struct node** head,struct node * n)
{
  n -> next = *head;
  *head = n;
}
#endif

#ifndef INSA
void insertAt(struct node** head,struct node * n,int index)
{
  struct node * temp = * head;
  if (index == 0){
    insertFirst(head, n);
  }
  else if (index == getLength(head)){
    insertLast(&temp,n);
  }
  else if(index > getLength(head) || index < 0){
    free(n);
  }
  else {
    for (int i = 0; i < index - 1; i++){
	temp = temp -> next;
    }
    n -> next = temp -> next;
    temp -> next = n;
  }
  
  return;
}
#endif

#ifndef INSL
void insertLast(struct node** head,struct node *n)
{
  struct node * last = *head;
  n -> next = NULL;
  if (*head == NULL){
    *head = n;
    return;
  }
  while (last -> next != NULL){
    last = last -> next;
  }
  last -> next = n;
}
#endif

#ifndef DELFM
void deleteFirstMatch(struct node**head,int value)
{
  struct node * temp = *head;
  struct node * prev;
  if (temp == NULL){
    return;
  }
  //delete if it is the first node
  if (temp -> value == value){
    *head = temp -> next;
    free(temp);
    return;
  }
  while (temp != NULL && temp -> value != value){
    prev = temp;
    temp = temp -> next;
  }
  if (temp == NULL){
    return;
  }
  prev -> next = temp -> next;
  free(temp);
}
#endif

#ifndef DelA
void deleteAt(struct node** head,int index)
{
  struct node * temp = *head;
  struct node * last;
  if (temp == NULL){
    return;
  }
  if (index == 0){
    *head = temp -> next;
    free(temp);
    return;
  }
  for (int i = 0; i < index - 1; i++){
    last = temp;
    temp = temp -> next;
  }
  if (temp == NULL){
    return;
  }
  else if (temp -> next == NULL){
    free(last -> next);
    last -> next = NULL;
  }
  struct node * next = temp -> next -> next;
  free(temp -> next);
  temp -> next = next;
}
#endif

#ifndef DELAM
void deleteAllMatches(struct node** head,int value)
{
  struct node * temp = *head;
  struct node * prev;
  //delete if it is the first node
  while (temp != NULL && temp -> value == value){
    *head = temp -> next;
    free(temp);
    temp = *head;
  }  
  while (temp != NULL){
    while(temp != NULL && temp -> value != value){
      prev = temp;
      temp = temp -> next;
    }
    if (temp == NULL){
      return;
    }
    prev -> next = temp -> next;
    free(temp);
    temp = prev -> next;
  }
}
#endif

#ifndef L
int getLength(struct node** head)
{
  int  count = 0;
  struct node * curr = *head;
  while (curr != NULL){
    count++;
    curr = curr -> next;
  }
  return count;
}
#endif

#ifndef FREEMEM
void freeMemory(struct node** head)
{
  struct node * temp;
  while (*head != NULL){
    temp = *head;
    *head = (*head) -> next;
    free(temp);
  }
}
#endif
