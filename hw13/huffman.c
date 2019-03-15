#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"


int* print_asc(FILE* fx,char* filename2,int* count){
  //	FILE* fp = fopen(filename,"r");
	FILE* fp2 = fopen(filename2,"w");
	/*	int* count = malloc(sizeof(int)*256);
	for(int i = 0;i < 256;i++){
		count[i] = 0;
	}*/	
	while(!feof(fx)){
	        unsigned char index = fgetc(fx);
		count[(int) index]++;
	}
	count[255]--;
	for (int i = 0;i < 256;i++){
	  fprintf(fp2,"%ld\n",(long)count[i]);
	}
	//	fclose(fx);
	fclose(fp2);
	return count;
}			



Node* pq_enqueue(Node** pq, char ch,int count){
	Node* new_node = malloc(sizeof(Node));
	Node* temp = *pq;	
	new_node -> ch = ch;
	new_node -> count = count;
	new_node -> left = NULL;
	new_node -> right = NULL;
	new_node -> next = NULL;
	
	if (*pq == NULL){
	        *pq = new_node;
     		return *pq;
	}
	if (new_node -> count < temp -> count || (new_node -> count == temp -> count && new_node -> ch < temp -> ch)){
		new_node -> next = temp;
		*pq = new_node;
		return new_node;
	}

    	while (temp -> next != NULL){
	  if(temp -> next -> count > new_node -> count){
	    break;
	  }
	  if(temp -> next -> count == new_node -> count && temp -> next -> ch > new_node -> ch){
	    break;
	  }
	  temp = temp -> next;
	}
	new_node -> next = temp -> next;
	temp -> next = new_node;
	return *pq;
}	

Node* stack_pop(Node** stack){
	Node* list = NULL;
	if (*stack == NULL){
	  return NULL;
	}
	list = (*stack);
	(*stack) = list -> next;
	list -> next = NULL;
	return list;
}

Node* enlist(int* count,Node* list){
        int i = 0;
        while (i < 256){
		if (count[i] != 0){
		  list = pq_enqueue(&list,(char)i,count[i]);
		    }
		i++;
	}
	return list;
}

Node* enbranch(Node* left,Node* right){
        Node* branch = malloc(sizeof(Node));
        branch -> ch = '\0';
	branch -> count = left -> count + right -> count;
	branch -> next = NULL;
	branch -> left = left;
	branch -> right = right;
	return branch;
}

Node* treequeue(Node** pq, Node* new_node){
	Node* temp = *pq;
	if (*pq == NULL){
		new_node->next = *pq;
		*pq = new_node;
		return *pq;
	}
	if (new_node -> count < temp -> count || (new_node -> count == temp -> count && new_node -> ch != 0)){
		new_node -> next = *pq;
		*pq = new_node;
		return *pq;
	}

    	while (temp -> next != NULL){
	  if(temp -> next -> count > new_node -> count){
	    break;
	  }
	  if(temp -> next -> count == new_node -> count && temp -> next -> ch > new_node -> ch && new_node -> ch != 0){
	    break;
	  }
	  temp = temp -> next;
	}
	new_node -> next = temp -> next;
	temp -> next = new_node;
	return *pq;
}

Node* entree(Node* list){
	while (list -> next != NULL){
		Node* left = stack_pop(&list);
		Node* right = stack_pop(&list);
		Node* branch = enbranch(left,right);
		treequeue(&list,branch);
	}
	return list;
}

int count_path(Node* list){
  Node* curr = list;
  int path = 0;
  while (curr -> right != NULL){
    curr = curr -> right;
    path++;
  }
  return path;
}

void print_freq(Node* list,char* filename){
	FILE* fp = fopen(filename,"w");
	while(list != NULL){
	  fprintf(fp,"%c",list->ch);
		fputc(':',fp);
		fprintf(fp,"%d",list -> count);
		fprintf(fp,"->");
		list = list -> next;
	}
	fprintf(fp,"NULL\n");
	fclose(fp);
	return;
}

void print_bits(Node* list, char* binary, int index, FILE* fp){
  if(list == NULL){
    return;
  }
  else if(list -> left == NULL){
    fputc(list -> ch, fp);
    fprintf(fp,":%s\n",binary);
    return;
  }
  else {
    binary[index] = '0';
    print_bits(list -> left, binary, index + 1, fp);
    binary[index] = '1';
    print_bits(list -> right,binary,index + 1, fp);
    binary[index] = 0;
  }
} 

void destory_node(Node* list){
  if (list->left == NULL){
    free(list);
    return;
  }
  else{
    destory_node(list->left);
    destory_node(list->right);
  }
  free(list);
}
