#include <stdio.h>
#include <stdlib.h>
#include "pa08.h"

void helpVID(char * string, int index, int len, char * val, int idx);

#ifndef CDOUBLE
void createDouble(char * string,DoubleVar* var,int index,bool dot,int len)
{
  for (int i = var -> digit_start;i <= var -> digit_end + 1;i++){
    int check = var -> digit_end + 1;
    if (index == len && dot == true && string[len - 1] != '.'){
      for (int ct = 0; ct < len;ct++){
	printf("%c",string[ct]);
      }
      printf("\n");
      return;
    }
    else if (index == len && dot == true && string[len - 1] == '.'){
      return;
    }
    else if (index == len && dot == false){
      return;
    }
    // i = end + 1 => '.'
    if (index == 0 && i == check){
      return;
    }
    else if (index == 0 && i != check){
      string[index] = i;
      createDouble(string,var,index + 1,dot,len);
    }
    else if (dot == false && i == check){
      dot = true;
      string[index] = '.';
      createDouble(string,var,index + 1,dot,len);
    }
    else if(dot == true && i == check){
      return;
    }
    else {
      string[index] = i;
      createDouble(string,var,index + 1,dot,len);
    }
  }
}
#endif

#ifndef CVID
void createVID(char * string,VIDVar * var,int index,int len){
  int idx = 0;
  char * val = malloc(((var -> upper_case_end - var -> upper_case_start) + (var -> lower_case_end - var -> lower_case_start) + (var -> digit_end - var -> digit_start) + 3) * sizeof(char));
  for (int j = var -> lower_case_start; j <= var -> lower_case_end;j++){
    val[idx] = j;
    idx++;
  }
  for (int k = var -> upper_case_start; k <= var -> upper_case_end;k++){
    val[idx] = k;
    idx++;
  }
  for (int i = var -> digit_start;i <= var -> digit_end;i++){
    val[idx] = i;
    idx++;
  }
  helpVID(string,index,len,val,idx);
  free(val);
}

void helpVID(char * string, int index, int len, char * val, int idx){
  for (int i = 0; i <= idx; i++){
    int check = idx;
    if (index == len && (string[0] > '9' || string[0] == '_')){
      for (int ct = 0; ct < len;ct++){
	printf("%c",string[ct]);
      }
      printf("\n");
      return;
    }
    else if(index == len && (string[0] >= '0' || string[0] <= '9')){
      return;
    }
    
    if (index == 0 && i != check){
      string[index] = val[i];
      helpVID(string,index + 1,len,val,idx);
    }
    else if (index == 0 && i == check){
      string[index] = '_';
      helpVID(string,index + 1,len,val,idx);
    }
    else if (i == check){
      string[index] = '_';
      helpVID(string,index + 1,len,val,idx);
    }
    else{
      string[index] = val[i];
      helpVID(string,index + 1,len,val,idx);
    }
  }
}
#endif

