#ifndef HUFFMAN_H
#define HUFFMAN_H
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef struct _Node {
	char ASC;
	int freq;
	struct _Node* next;
	struct _Node* left;
	struct _Node* right;
}Node;

int array_path(Node* list);
int* printASC(FILE* filename1, char* filename2, int* count);
void destory_node(Node* list);
void print_freq(Node* list,char* filename3);
void print_results(Node* list, char* binary, int i, FILE* filename4);
Node* pq_enqueue(Node** pq, char ASC, int count);
Node* treequeue(Node** pq, Node* new_node);
Node* build_tree(Node* tree);
Node* build_branch(Node* left, Node* right);
Node* linked_list(int* count, Node* list);
Node* stack_pop(Node** stack);



#endif

