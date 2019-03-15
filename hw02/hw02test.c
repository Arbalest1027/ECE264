#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "hw02.h"

int main(int argc,char* argv[]){

	print_integer(INT_MIN,10,"");
	printf("\n");
	print_integer(INT_MAX,10,"");
	printf("\n");
	print_integer(-123,2,"$");
	printf("\n");
	print_integer(4143212,16,"0x");
	printf("\n");
	print_integer(123,10,"");print_integer(-213,2,"0b");

	return EXIT_SUCCESS;
}
