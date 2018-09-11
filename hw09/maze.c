#include <stdio.h>
#include <stdlib.h>
#include "maze.h"

void find_maze_dimensions(FILE * fp, int * a_num_rows, int * a_num_cols) {
   *a_num_rows = *a_num_cols = 0;
   fseek(fp,0,SEEK_SET);
	while (fgetc(fp) != '\n')
	{
		(* a_num_cols)++;
	}
   fseek(fp,0,SEEK_SET);
	while (fgetc(fp) != EOF)
	{
		if(fgetc(fp) == '\n')
		{
		(* a_num_rows)++;
		}
	}
}

int find_opening_location(FILE * fp) {
	int open = 0;
	fseek(fp,0,SEEK_SET);
	while (fgetc(fp) != PATH)
	{
		open++;
	}
   return open;
}

int count_path_locations(FILE * fp) {
	fseek(fp,0,SEEK_SET);
	int count = 0;
	char c;
	while (!feof(fp))
	{
		c = fgetc(fp);
		if (c  == PATH)
		{
			count = count + 1;
		}
	}
   return count;
}
char get_location_type(FILE * fp, int row, int col) {
	int rows = 0;
	int cols = 0;
	int location = 0;
	char type;
	fseek(fp,0,SEEK_SET);
	while (fgetc(fp) != '\n')
	{
		cols++;
	}
	fseek(fp,0,SEEK_SET);
	while (fgetc(fp) != EOF)
	{
		if (fgetc(fp) == '\n')
		{
			rows++;
		}
	}
	location = row * cols + col + row;
	fseek(fp,location,SEEK_SET);
	type = fgetc(fp);
	return type;
}
 
int represent_maze_in_one_line(char * filename, FILE * fp) {
	char sq;
	int location = 0;
	FILE * faker = fopen(filename,"w");
	fseek(fp,0,SEEK_SET);
	if (faker == NULL)
	{
		return MAZE_WRITE_FAILURE;
	}
	sq = fgetc(fp);
	while (!feof(fp))
	{
		if (sq != '\n')
		{
			fputc(sq,faker);
			location++;
		}
		sq = fgetc(fp);
	}
	fclose(faker);
   return location;
}
