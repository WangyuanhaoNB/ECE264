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
	print_freq(node,argv[3]);
	node = build_tree(node);
	FILE* inp = fopen(argv[4],"w");
	int path = array_path(node);
	char* ch = calloc(path,sizeof(char*));
	print_results(node,ch,0,inp);
	fclose(inp);
	fclose(filename1);
	free(asc);
	free(ch);
	destory_node(node);


	return EXIT_SUCCESS;
}
