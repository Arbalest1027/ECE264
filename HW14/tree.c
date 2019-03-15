#include <stdbool.h>

#include "tree.h"


#ifndef TREE_CREATE

TreeNode * TreeNodeCreate(unsigned char val, int freq)
{
	//creates a tree node from the input and returns the TreeNode *
	// change NULL in return  to the newly created TreeNode *
  TreeNode * tn = malloc(sizeof(TreeNode));
  tn -> left = NULL;
  tn -> right = NULL;
  tn -> data = val;
  tn -> freq = freq;
  return tn;
}
#endif



#ifndef TREE_MERGE
// Following code merges two treenodes into one treenode and retun the new tree node
TreeNode * TreeMerge(TreeNode * treeNode1, TreeNode * treeNode2){
	// This function merges two TreeNode*s by creating a new TreeNode*. 
	// It uses HUFF_ELEM as `data` for new TreeNode and 
	// sum of the frequencies of two TreeNode*s becomes the value of frequency variable of the new TreeNode\*.
	// smaller of the two frequencies of input TreeNode* should become the left child of this newly created TreeNode.
	// change NULL in return to the newly created TreeNode *
  TreeNode * new_tree = malloc(sizeof(TreeNode));
  /* if (treeNode1 -> freq <= treeNode2 -> freq){
    new_tree -> left = treeNode1;
    new_tree -> right = treeNode2;
  }
  else if (treeNode1 -> freq > treeNode2 -> freq){
    new_tree -> left = treeNode2;
    new_tree -> right = treeNode1;
    }*/
  new_tree -> left = treeNode1;
  new_tree -> right = treeNode2;
  new_tree -> freq = treeNode1 -> freq + treeNode2 -> freq;
  new_tree -> data = HUFF_ELEM;
  return new_tree;
}
#endif


#ifndef TREE_PREFIX_PRINT
// Prefix/Preorder Tree Print
// Do not worry about level for this assignment, keep it any value. 
void PrefixTreePrint(TreeNode *treeNode, int level){
  	// Print the tree in Pre-order
	// use PrintSingleHelper function to print the values
  level = 0;
  if (treeNode == NULL){
    return;
  }
  PrintSingleHelper(treeNode);
  PrefixTreePrint(treeNode -> left,level);
  PrefixTreePrint(treeNode -> right,level);
  return;
}

#endif

#ifndef TREE_CLEAN

void CleanTree(TreeNode *treeNode){
	// Clean the tree
  if (treeNode == NULL){
    return;
  }
  CleanTree(treeNode -> left);
  CleanTree(treeNode -> right);
  free(treeNode);
}

#endif
/******************** DO NOT MODIFY THE BELOW HELPER FUNCTION *********************/

#ifndef SOL
void PrintSingleHelper(TreeNode *treeNode){
  printf("Char: %c, Freq: %d\n", treeNode->data, treeNode->freq);
}
#endif
