#include<stdio.h>
#include<stdlib.h>
#include "huffman.h"

int* printASC(FILE* filename1, char* filename2, int* count)
{
	FILE* input = fopen(filename2,"w");
	while (!feof(filename1))
	{
		unsigned char i = fgetc(filename1);
		count[(int)i]++;
	}
	count[255] = count[255] - 1;
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

void print_output1(Node* node, char* bin, int i, FILE* inp)
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
		print_output1(node -> left, bin,i+1,inp);
		bin[i] = '1';
		print_output1(node -> right,bin,i+1,inp);
		bin[i] = 0;
	}
}

void print_output2(Node* node, FILE* inp)
{
	if (node == NULL)
	{
		return;
	}
	if (node -> left == NULL)
	{
		fprintf(inp,"%d",1);
		fputc(node->ASC,inp);
		return;
	}
    else
	{
		print_output2(node -> left,inp);
		print_output2(node -> right,inp);
		fprintf(inp,"%d",0);
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

void print_output3(FILE* inp, FILE* inp3)
{
	int count = 0;
	int i = 0;
	char d;

	while (!feof(inp))
	{
		count++;
		fgetc(inp);
	}
	char* header = calloc(count,sizeof(char));
	fseek(inp,0,SEEK_SET);
	while (!feof(inp))
	{
		d = fgetc(inp);
		if (d == EOF)
		{
			break;
		}
		header[i] = d;
		i++;
	}
	int a = 0;
	int n = 0;
	unsigned char b = '\0';
	unsigned char c = 0;
	char temp = header[a];
	while (temp != '\0')
	{
		if (header[a] == '0')
		{
			b = b << 1;
			n++;
			if (n == 8)
			{
				fputc(b,inp3);
				n = 0;
				b = 0;
			}
		}
		else
		{
			b <<= 1;
			b += 1;
			n++;
			a++;
			if (n == 8)
			{
				fputc(b, inp3);
				n = 0;
				b = 0;
			}
			b = b << (8 - n);
			c = header[a] >> n;
			b += c;
			c = 0;
			fputc(b, inp3);
			b = 0;
			b = ((header[a] << (8 - n)) >> (8 - n));
		}
		a++;
		temp = header[a];
	}
}

