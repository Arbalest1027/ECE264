#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pe11.h"
#define MAX_LENGTH 100

int main(int argc, char **argv) {
  FILE * fp = fopen(argv[1],"r");
  char * token;
  char command[MAX_LENGTH];
  int value;
  struct node * head = NULL;
  int count = 0;
  while (fgets(command, MAX_LENGTH,fp) != NULL){
    token = strtok(command," ");
    count = 0;
    if (!strcmp(token,"L")){
      printf("%d\n",getLength(&head));
    }
    else if (!strcmp(token,"insF")){
      struct node * n = malloc(sizeof(nodeType));
      while (token != NULL){
	token = strtok(NULL," ");
	count++;
	if (count == 1){
	  value = atoi(token);
	  n -> value = value;
	}
      }
      insertFirst(&head,n);
      print(&head);
    }
    else if(!strcmp(token,"insL")){
      struct node * n = malloc(sizeof(nodeType));
      while (token != NULL){
	token = strtok(NULL," ");
	count++;
	if (count == 1){
	  value = atoi(token);
	  n -> value = value;
	}
      }
      insertLast(&head,n);
      print(&head);
    }
    else if (!strcmp(token,"insA")){
      struct node * n = malloc(sizeof(nodeType));
      while (token != NULL){
	token = strtok(NULL," ");
	count++;
	if (count == 1){
	  value = atoi(token);
	  n -> value = value;
	}
	else if (count == 2){
	  insertAt(&head,n,atoi(token));
	  print(&head);
	}
      }
    }
    else if (!strcmp(token,"delFM")){
      while (token != NULL){
	token = strtok(NULL," ");
	count++;
	if (count == 1){
	  deleteFirstMatch(&head,atoi(token));
	  print(&head);
	}
      }
    }
    else if (!strcmp(token,"delAM")){
      while (token != NULL){
	token = strtok(NULL," ");
	count++;
	if (count == 1){
	  deleteAllMatches(&head,atoi(token));
	  print(&head);
	}
      }
    }
    else if (!strcmp(token,"delA")){
      while (token != NULL){
	token = strtok(NULL," ");
	count++;
	if (count == 1){
	  deleteAt(&head,atoi(token));
	  print(&head);
	}
      }
    }
  }
  fclose(fp);
  freeMemory(&head);
  return EXIT_SUCCESS;
}
