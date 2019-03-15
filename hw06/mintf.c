#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "mintf.h"

void conversion(unsigned int, int);

void mintf(const char *format, ...){
	const char *output;
	int i;//store any integer transformation
	double j;//store double
	char *s;//store string
	//get multi variables
	va_list arg;
	va_start(arg,format);

	for (output = format; *output != '\0';output++){
		//print if not encounter any %
		if (*output != '%'){
			fputc(*output,stdout);
		}
		else{
		output++;
		//switch case for different variables after %
		switch(*output){
			case 'd' : i = va_arg(arg,int);//print integer in decimal
						print_integer(i,10,"");
						break;
			case 'x' : i = va_arg(arg,int);//in hex
						print_integer(i,16,"0x");
						break;
			case 'b' : i = va_arg(arg,int);//in binary
						print_integer(i,2,"0b");
						break;
			case '$' : j = va_arg(arg,double);//display 2 decimal places
						if (j < 0){
							j = -j;
							fputc('-',stdout);
						}
						fputc('$',stdout);
						int intpart = (int)j;
						print_integer(j,10,"");
						fputc('.',stdout);
						double decpart = j - intpart;
						if (decpart != 0){
							print_integer((int)(decpart*100),10,"");
						}
						else{
							fputc('0',stdout);
							fputc('0',stdout);
						}	
						break;
			case 's' : s = va_arg(arg,char *);//display string
						int count = 0;
						while (s[count] != '\0'){
							fputc(s[count],stdout);
							count++;
						}	
						break;
			case 'c' : i = va_arg(arg,int);	//display ascii code		
						fputc(i,stdout);
						break;
			case '%' : fputc('%',stdout);//display %
						break;
			default  : if (*output == '\0'){//display any other characters after %
						fputc('%',stdout);
						}
						else {
						fputc('%',stdout);
						fputc(*output,stdout);
						}
			}
	
		}
    }	
	va_end(arg);//End of getting the parameters
}

void print_integer(int n, int radix, char* prefix){
	unsigned int n_abs = n;
	if (n < 0){
		fputc('-',stdout);
		n_abs = -n;
	}
	fputs(prefix,stdout);
	if (n == 0){
		fputc('0',stdout);
		return;
	}	
	//convert
	conversion(n_abs,radix);
}

void conversion(unsigned int n, int radix){
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
