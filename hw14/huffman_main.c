#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"


int main(int argc, char* argv[]) 
{
  	FILE* fx = fopen(argv[1],"r");
        int*  count = malloc(sizeof(int*) * 256);
        for (int i = 0; i < 256; i++){
	      count[i] = 0;
        }
        count = print_asc(fx,count);
	Node* list = NULL;
	list = enlist(count,list);
	list = entree(list);
	FILE* fp = fopen(argv[2],"w");
	int path = count_path(list);
	char* bits_a = calloc(path,sizeof(char*));
	print_bits(list,bits_a,0,fp);
	fclose(fx);
	fclose(fp);
	free(count);
	free(bits_a);
	FILE* fi = fopen(argv[3],"w");
	print_char(list,fi);
	fputc('0',fi);
	fclose(fi);
	FILE* fo = fopen(argv[4],"w");
	print_bit(fo,argv[3]);
	fclose(fo);
	destory_node(list);
	return EXIT_SUCCESS;
}
