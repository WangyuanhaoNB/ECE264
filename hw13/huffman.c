#include<stdio.h>
#include<stdlib.h>
#include"huffman.h"

int* printASC(FILE* filename1, char* filename2, int* count)
{
	FILE* input = fopen(filename2,"w");
	while (!feof(filename1))
	{
		unsigned char i = fgetc(filename1);
		count[(int)i]++;
	}
	count[255] = count[255] - 1;
    int	i = 0;
	while (i < 256)
	{
		fprintf(input,"%ld\n",(long)count[i]);
		i++;
	}
	fclose(input);
	return count;
}

Node* pq_enqueue(Node** pq, char ASC, int freq)
{
	Node* current = malloc(sizeof(Node));
	Node* temp = *pq;
	current -> ASC = ASC;
	current -> freq = freq;
	current -> next = NULL;
	current -> left = NULL;
	current -> right = NULL;
	
	if(*pq == NULL)
	{
		*pq = current;
		return *pq;
	}
	if (current -> freq < temp -> freq || (current -> freq == temp -> freq && current -> ASC < temp -> ASC))
	{
		current -> next = temp;
		*pq = current;
		return current;
	}
	while (temp -> next != NULL)
	{
		if (temp -> next -> freq > current -> freq)
		{
			break;
		}
		if (temp -> next -> freq == current -> freq && temp -> next -> ASC > current -> ASC)
		{
			break;
		}
		temp = temp -> next;
	}
	current -> next = temp -> next;
	temp -> next = current;
	return *pq;
}

Node* stack_pop(Node** stack)
{
	Node* node = NULL;
	if (*stack == NULL)
	{
		return NULL;
	}
	node = (*stack);
	(*stack) = node -> next;
	node -> next = NULL;
	return node;
}

Node* linked_list(int* freq, Node* node)
{
	int i = 0;
	for (i = 0; i < 256; i++)
	{
		if (freq[i] != 0)
		{
			node = pq_enqueue(&node,(char)i,freq[i]);
		}
	}
	return node;
}

Node* build_branch(Node* left, Node* right)
{
	Node* node = malloc(sizeof(Node));
	node -> ASC = '\0';
	node -> freq = left -> freq + right -> freq;
	node -> next = NULL;
	node -> left = left;
	node -> right = right;
	return node;
}

Node* treequeue(Node** pq, Node* current)
{
	Node* temp = *pq;
	if (*pq == NULL)
	{
		current -> next = *pq;
		*pq = current;
		return *pq;
	}

if (current -> freq < temp -> freq || (current -> freq == temp-> freq && current -> ASC != 0))
{
	current -> next = *pq;
	*pq = current;
	return *pq;
}

while (temp -> next != NULL)
{
	if (temp -> next -> freq > current -> freq)
	{
		break;
	}
	if (temp -> next -> freq == current -> freq && temp -> next -> ASC > current -> ASC && current -> ASC != 0)
	{
		break;
	}
	temp = temp -> next;
}
current -> next = temp -> next;
temp -> next = current;
return *pq;
}

Node* build_tree(Node* tree)
{
	while(tree -> next != NULL)
	{
		Node* left = stack_pop(&tree);
		Node* right = stack_pop(&tree);
		Node* branch = build_branch(left,right);
		treequeue(&tree, branch);
	}
	return tree;
}

int array_path(Node* node)
{
	Node* road = node;
	int path = 0;
	while (road -> right != NULL)
	{
		road = road -> right;
		path++;
	}
	return path;
}

void print_freq(Node* node, char* filename)
{
	FILE * input = fopen(filename,"w");
	while (node != NULL)
	{
		fprintf(input,"%c",node -> ASC);
		fputc(':',input);
		fprintf(input,"%d",node -> freq);
		fprintf(input,"->");
			node = node -> next;
	}
	fprintf(input,"NULL\n");
	fclose(input);
	return;
}

void print_results(Node* node, char* bin, int i, FILE* inp)
{
	if (node == NULL)
	{
		return;
	}
	else if (node -> left == NULL)
	{
		fputc(node->ASC,inp);
		fprintf(inp,":%s\n",bin);
		return;
	}
	else
	{
		bin[i] = '0';
		print_results(node -> left, bin,i+1,inp);
		bin[i] = '1';
		print_results(node -> right,bin,i+1,inp);
		bin[i] = 0;
	}
}

void destory_node(Node* node)
{
	if (node->left == NULL)
	{
		free(node);
		return;
	}
	else
	{
		destory_node(node->left);
		destory_node(node->right);
	}
	free(node);
}

