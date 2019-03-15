#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pe10.h"




#ifndef PRINT
// This function will print the boolean array with length=len in the following format.
// It will print out the index if its corresponding value in the array is true, Otherwise it will print X instead.
// If the array is of length 4, and it has values of true(index=0),false(index=1),true(index=2),false(index=3)
// the output looks like this: 0,X,2,X
// ::::::::IMPORTANT NOTES:::::::
// 1- There should be no extra comma at the end nor at the beginning, "Violating this format will get you zero".
// 2- Make sure that there is a new line at the end of the output (i.e printf("\n")). 
void print(bool * arr,int len)
{
  for (int i = 0; i < len;i++){
    if (i == len - 1){
      if (arr[i] == false){
	printf("X");
      }
      else if (arr[i] == true){
	printf("%d",i);
      }
    }else {
      if (arr[i] == false){
	printf("X,");
      }
      else if (arr[i] == true){
	printf("%d,",i);
      }
    }
  }
  printf("\n");
}
#endif


#ifndef JOSEPHUS
// arr: a boolean array which you should initialized to 1's in the main.c.
// len: the length of the array
// k:   the numbers of elements you should skip
// p:   if the number of remaining elements in the array after each step is divisible by p, then you need to print the array.
// Your function should stop when it has only one element left.
void josephus(bool * arr, int len, int k,int p)
{
  int remain = len;
  int i = 0;
  int count = 0;
  int alive = 0;
  while (remain > 1){
    alive = 0;
    count = 0;
    while (arr[i] == false){
      i++;
      if (i == len){
	i = 0;
      }
    }
    while (count != k){
      if (arr[i] == true){
	count++;
      }
      i++;
      if (i == len){
	i = 0;
      }
    }
    while (arr[i] == false){
      i++;
      if (i == len){
	i = 0;
      }
    }
    arr[i] = false;
    remain--;
    for (int ct = 0;ct < len;ct++){
      if (arr[ct] == true){
	alive++;
      }
    }
    if (alive % p == 0){
      print(arr,len);
    }
  }
}
#endif
