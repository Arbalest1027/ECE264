#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "mintf.h"
#include <limits.h>

int main(int argc,char* argv[]){
	mintf("haha");
	printf("\n");
	mintf("a");
	fputc('\n',stdout);
	mintf("Check for the hex and binary of %d: %x %b",123,123,123);
	fputc('\n',stdout);
	mintf("Print ascII code of %d: %c",56,56);
	fputc('\n',stdout);
	mintf("Decimal point!:%$",78.57983);
	fputc('\n',stdout);
	mintf("%%,%z,%w");
	fputc('\n',stdout);
	mintf("hi%d,hello%$,zup,%s\n",0,-32.3412,"abc");
	fputc('\n',stdout);
	mintf("123123,%d,%c,%",INT_MIN,'a');
	fputc('\n',stdout);
	mintf("%x,%",-123);

	return EXIT_SUCCESS;
}	
