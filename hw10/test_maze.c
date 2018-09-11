#include<stdio.h>
#include<stdlib.h>
#include "maze.h"

int main(int argc, char* argv[])
{
	FILE * fp = fopen("sample.2.7x9","r");
	if (fp == NULL)
	{
		return EXIT_FAILURE;
	}

	Maze* orig = read_maze(fp);

	Maze* taller = make_taller(orig);
		
	write_maze("expected.txt",taller);
	free_maze(taller);
	Maze* wider = make_wider(orig);
	
	write_maze("expected.txt",wider);

	free_maze(wider);
	//free_maze(taller);
	free_maze(orig);

	fclose(fp);

	return EXIT_SUCCESS;
}
