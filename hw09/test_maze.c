#include<stdio.h>
#include<stdlib.h>
#include "maze.h"

int main(int argc, char** argv)
{
	FILE * fp = fopen("sample.2.7x9","r");
	if(fp == NULL)
	{
		return EXIT_FAILURE;
	}

	int row;
	int col;
	char* filename = argv[1];
	find_maze_dimensions(fp,&row,&col);
	printf("%d,%d\n",row,col);
	int open = find_opening_location(fp);
	printf("%d\n",open);
	int path = count_path_locations(fp);
	printf("%d\n",path);
	char location = get_location_type(fp,0,4);
	printf("%c\n",location);
	int size = represent_maze_in_one_line(filename,fp);
	printf("%d\n",size);
	fclose(fp);

	return EXIT_FAILURE;
}
