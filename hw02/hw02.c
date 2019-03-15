#include "hw02.h"
#include <stdio.h>

void conversion(unsigned int,int);
void print_integer(int n,int radix, char* prefix)
{
	unsigned int n_abs = n;
	int count = 0;
	int index2 = 0;//loop control
	//get minus sign if there is one		
	if (n < 0){
		fputc('-',stdout);
	}
	//print prefix
	while (prefix[count] != '\0'){
		count++;
	}
	while (count != 0){
		fputc(prefix[index2],stdout);
		count--;
		index2++;
	}
	//prepare the variable for recursion
	if (n < 0){
	n_abs = -n;
	}
	//convert by conversion
	conversion(n_abs,radix);
}
void conversion(unsigned int n,int radix)
{
	int rem;//remainder
	if (n != 0){
		rem = n % radix;
		n /= radix;
		conversion(n,radix);
		if (rem < 10){
		fputc(rem + '0',stdout);
		}
		else{
		fputc(rem - 10 + 'a',stdout);
		}
	}
}
