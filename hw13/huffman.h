#ifndef huffman
#define huffman
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct _Node{
	char ch;
	int count;
	struct _Node* next;
	struct _Node* left;
	struct _Node* right;
}Node;	
int count_path(Node* list);

void destory_node(Node* list);

int* print_asc(FILE* fx,char* filename2,int* count);

void print_freq(Node* list,char* filename);

Node* pq_enqueue(Node** pq, char ch, int count);

Node* stack_pop(Node** stack);

Node* enlist(int* count, Node* list);

Node* treequeue(Node** pq, Node* new_node);

Node* entree(Node* tree);

Node* enbranch(Node* left,Node* right);

void print_bits(Node* list, char* binary, int index, FILE* fp);
#endif
