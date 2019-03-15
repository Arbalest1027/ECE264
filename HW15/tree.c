#include "tree.h"


#ifndef USIGN_TO_BIN
// function to create binary values from the input char values
char * UnSig2Bin(unsigned char value) {
  char * bin = malloc(8);
  unsigned char mask = 0x01;
  for (int i = 7; i >= 0;i--){
    bin[i] = (mask & value) == mask;
    if (bin[i]){
      bin[i] = '1';
    }else {
      bin[i] = '0';
    }
    mask = mask << 1;
  }
  return bin;
}

#endif

#ifndef WRITE_BINARY

// WriteInOrderBinary takes root and file * as input
// and creates binary representation of the tree as specified in the example
int WritePreOrderBinary(TreeNode * root, FILE *outptr){
  if (root == NULL){
    return EXIT_FAILURE;
  }
  if (root -> leftChild == NULL && root ->rightChild == NULL){
    char * bin = UnSig2Bin(root -> data);
    fprintf(outptr,"1");
    fwrite(bin,sizeof(char),8,outptr);
    free(bin);
    return EXIT_SUCCESS;
  }
  fprintf(outptr,"0");
  WritePreOrderBinary(root -> leftChild,outptr);
  WritePreOrderBinary(root -> rightChild,outptr);
  return EXIT_SUCCESS;
}

int CreateBinaryFromTree(TreeNode * root, const char *outfile){
  FILE * fo = fopen(outfile,"wb");
  FILE * temp = tmpfile();
  int i = 0;
  unsigned char output = 0x00;
  unsigned char mask = 0x80;
  int bit;
  int ret = WritePreOrderBinary(root,fo);
  while (!feof(temp)){
    bit = fgetc(temp);
    if (bit != EOF){
      if (bit == '1'){
	output = mask | output;
	mask = mask >> 1;
      }
      else {
	mask = mask >> 1;
      }
      i++;
      if (i == 8){
	fwrite(&output,sizeof(unsigned char),1,fo);
	i = 0;
	output = 0x00;
	mask = 0x80;
      }
    }
  }
  fwrite(&output,sizeof(unsigned char),1,fo);
  fclose(fo);
  fclose(temp);
  return ret;
}

#endif





#ifndef CLEAN_TREE

void CleanTree(TreeNode * root){
  if (root -> leftChild == NULL){
    free(root);
    return;
  }
  else{
    CleanTree(root -> leftChild);
    CleanTree(root -> rightChild);
  }
  free(root);
}
#endif





#ifndef BINARY_SEARCH_TREE

int IntCompare(const void * val1, const void * val2){
  return (*(unsigned char*)val1 - *(unsigned char*)val2);
}

TreeNode * CreateBinarySearchTree(long randomSeed, long numNodes){
  unsigned char * binArray = malloc(sizeof(unsigned char)*numNodes);
  if(binArray == NULL){
    printf("Memory allocation to array failed\n" );
    return NULL;
  }
  srand(randomSeed);
  // allocate values to array
  for(int index = 0; index < numNodes ; index++){
    binArray[index] = rand() % 256;
  }
  // sort the array
  qsort(binArray, numNodes, sizeof(unsigned char), IntCompare);

  // create bst from the sorted array
  TreeNode * root = CreateBST(binArray, 0, numNodes-1);
  free(binArray);
  return root;

}
// TreeNode *CreateBSTHelper()
TreeNode* CreateTreeNode(unsigned char value){
  TreeNode *newNode = malloc(sizeof(TreeNode));
  newNode->data = value;
  newNode->leftChild = NULL;
  newNode->rightChild = NULL;
  return newNode;
}

TreeNode *CreateBST(unsigned char *sortedArray, int start , int end){
  // int len = sizeof(sortedArray)/sizeof(int);
  if(start > end) return NULL;
  int mid = (start+end)/2;
  TreeNode *newNode = CreateTreeNode(sortedArray[mid]);
  newNode->leftChild = CreateBST(sortedArray, start, mid -1);
  newNode->rightChild = CreateBST(sortedArray, mid +1, end);
  return newNode;

}
#endif
