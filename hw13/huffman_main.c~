#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"


int main(int argc, char* argv[]) 
{
        int*  count = malloc(sizeof(int*) * 256);
        for (int i = 0; i < 256; i++){
	      count[i] = 0;
        }
	FILE* fx = fopen(argv[1],"r");
        count = print_asc(fx,argv[2],count);

	Node* list = NULL;
	list = enlist(count,list);
	print_freq(list,argv[3]);
	list = entree(list);
	FILE* fp = fopen(argv[4],"w");
	int path = count_path(list);
	char* bits_a = calloc(path,sizeof(char*));
	print_bits(list,bits_a,0,fp);
	fclose(fp);
	fclose(fx);
	free(count);
	free(bits_a);
	destory_node(list);
	return EXIT_SUCCESS;
}
