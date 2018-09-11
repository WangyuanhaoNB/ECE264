#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"


int main(int argc, char* argv[]) 
{
	if (argc != 5)
	{
		return EXIT_FAILURE;
	}
	int* asc = malloc(sizeof(int*)*256);
	for (int i = 0; i<256; i++)
	{
		asc[i] = 0;
	}
	FILE* filename1 = fopen(argv[1],"r");
	asc = printASC(filename1,argv[2],asc);

	Node* node = NULL;
	node = linked_list(asc,node);
	node = build_tree(node);
	FILE* inp1 = fopen(argv[2],"w");
	FILE* inp2 = fopen(argv[3],"w");
	FILE* inp3 = fopen(argv[4],"w");
	int path = array_path(node);
	char* ch = calloc(path,sizeof(char*));
	print_output1(node,ch,0,inp1);
	print_output2(node,inp2);
	fputc('0',inp2);
	fclose(inp2);
	FILE* inp = fopen(argv[3],"r");
	print_output3(inp,inp3);
	fclose(inp);
	fclose(inp1);
	fclose(inp3);
	fclose(filename1);
	free(asc);
	free(ch);
	destory_node(node);


	return EXIT_SUCCESS;
}
