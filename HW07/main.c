#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "pe07.h"
#define MAX_LENGTH 100 //The maximum length of string


int main(int argc, char *argv[]) 
{
  FILE * fp = fopen(argv[1],"r");
  if(fp == NULL){
	printf("Fail to open the file");
  }
  int character;
  int line = 0;
  fseek(fp,0,SEEK_SET);
  while (!feof(fp)){
    character = fgetc(fp); 
    if (character == '\n'){
      line++;
    }
  }
  fseek(fp,0,SEEK_SET);
  bool integer;
  bool doub;
  bool ident;
  char * input;
  input = malloc(sizeof(char) * MAX_LENGTH);
  for (int i = 0;i < line; i++){

    fscanf(fp,"%s\n",input);
    if (argv[2] == NULL){
      if (input == NULL){
      }
      else{
	integer = IsInteger(input,0);
	doub = IsDouble(input,0,false);
	ident = IsValidIdentifier(input,0);
	if (integer == true){
	  printf("Integer\n");
	}
	else if (doub == true){
	  printf("Double\n");
	}
	else if (ident == true){
	  printf("Identifier\n");
	}
	else{
	  printf("None\n");
	}
      }
    }
    else if (!strcmp(argv[2],"-I")){
      integer = IsInteger(input,0);
      if (integer != false){
	printf("Integer\n");
      }
      else{
	printf("Not integer\n");
      }
    }
    else if (!strcmp(argv[2],"-D")){
      doub = IsDouble(input,0,false);
      if (doub == true){
	printf("Double\n");
      }
      else {
	printf("Not double\n");
      }
    }
    else if (!strcmp(argv[2],"-VID")){
      ident = IsValidIdentifier(input,0);
      if (ident == true){
	printf("Identifier\n");
      }
      else {
	printf("Not identifier\n");
      }
    }

  }
  free(input);
  fclose(fp);
  return EXIT_SUCCESS;
}
