#include "list_node.h"

// Create the list node from treenode as input
#ifndef LIST_CREATE
ListNode * ListNodeCreate(TreeNode * treenode){
  ListNode * new_node = malloc(sizeof(ListNode));
  new_node -> treeNodePtr = treenode;
  new_node -> next = NULL;
  return new_node;
}

#endif

#ifndef LIST_BUILD
ListNode * ListBuild(CharFreq * freqArray){
  // find the first index with non-zero frequency
  // if all are character have zero freq then return nothing
  ListNode * head = NULL;
  int i = 0;
  while (freqArray[i].freq == 0){
    i++;
  }
  if (i == NUMLETTER){
    return NULL;
  }
  // build the linked list such that lower frequency comes first and then higher
  while (i < NUMLETTER){
    TreeNode * tn = TreeNodeCreate(freqArray[i].data, freqArray[i].freq);
    ListNode * ln = ListNodeCreate(tn);
    head = ListInsert(head,ln);
    i++;
  }
  return head;
}
#endif




#ifndef LIST_INSERT

ListNode * ListInsert(ListNode * head, ListNode * listNode){
  // insert such that lower frequency comes before the already inserted frequency
  // if the frequencies are same for the nodes, then inserted node should come after the compared node
  if (head == NULL){
    return listNode;
  }
  if (head -> treeNodePtr -> freq > listNode -> treeNodePtr -> freq){
    listNode -> next = head;
    return listNode;
  }
  head -> next = ListInsert(head -> next, listNode);
  return head;
}

#endif

#ifndef LIST_CLEAN

void CleanList(ListNode *head){
  // clean the ListNode
  free(head);
}

#endif

#ifndef HUFFMAN_BUILD
// builds the huffman tree from the linked list
ListNode * BuildHuffmanTree(ListNode *head){
  while (head -> next != NULL){
    ListNode * next = head -> next;
    ListNode * nextnext = next -> next;
    TreeNode * tn = head -> treeNodePtr;
    TreeNode * tn_next = next -> treeNodePtr;
    free(head);
    free(next);
    head = nextnext;
    TreeNode * combine = TreeMerge(tn,tn_next);
    ListNode * ln = ListNodeCreate(combine);
    head = ListInsert(head,ln);
  }
  return head;
}

#endif
