#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "pe07.h"




#ifndef INT
bool IsInteger(char* str, int index)
{
  /*while (str[index] != '\0'){
    if (str[index] == '\n'){
      return true;
    }
    if (!isdigit(str[index])){
      return false;
    }
    index++;
  }
  return true;*/
  if (str[index] != '\0'){
    if (str[index] > '9' || str[index] < '0'){
      return false;
    }
    else {
      return IsInteger(str, index + 1);
    }
  }
  return true;
}
#endif

#ifndef DOUBLE
bool IsDouble(char* str, int index,bool dot)
{
  if (str[index] != '\0'){
    if ((str[index] > '9' || str[index] < '0') && str[index] != '.'){
      return false;
    }
    else if (str[0] == '.'){
      return false;
    }
    else if (str[index] == '.' && dot == true){
      return false;
    }
    else {
      if (dot == true && (str[index] > '9' || str[index] < '0')){
	return false;
      }
      if (str[index] == '.'){
	dot = true;
      }
      return IsDouble(str, index + 1, dot);
    }
  }
  else if (str[index] == '\0'){
    if (str[index - 1] == '.'){
      return false;
    }
    else if (dot == false){
      return false;
    }
  }
  
  return true;
}
#endif

#ifndef VALIDID
bool IsValidIdentifier(char* str, int index)
{
  if (str[index] != '\0'){
    if (index == 0){
      if (str[index] != '_' && !isalpha(str[index])){
	return false;
      }
      return IsValidIdentifier(str, index + 1);
    }
    if (str[index] != '_' && !isalpha(str[index]) && (str[index] > '9' || str[index] < '0')){
      return false;
    }
    else {
      return IsValidIdentifier(str, index + 1);
    }
  }
  return true;
}
#endif
