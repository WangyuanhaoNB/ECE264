#include <stdio.h>
#include <stdlib.h>
#include "maze.h"

Maze * malloc_maze(int num_rows, int num_cols)
{
  Maze * m = malloc(sizeof(Maze));
  m -> num_rows = num_rows;
  m -> num_cols = num_cols;
  if(m == NULL)
  {
	  free(m);
	  return NULL;
 }

  m -> cells = malloc(sizeof(*(m -> cells)) * num_rows);
  if (m -> cells == NULL)
  {
	  free(m -> cells);
	  free(m);
	  return NULL;
  }

  for (int i = 0; i < num_rows; i++)
  {
	  m -> cells[i] = malloc(sizeof(**(m -> cells)) * num_cols);
	  if (m -> cells[i] == NULL)
	  {
		  free(m -> cells[i]);
		  free(m -> cells);
		  free(m);
		  return NULL;
	  }
  }
	return m;
}

void free_maze(Maze * maze)
{
	if (maze == NULL)
	{
	}
	for (int i = 0; i < maze -> num_rows; i++)
	{
		free(maze -> cells[i]);
	}
	free(maze -> cells);
	free(maze);
}

Maze * read_maze(FILE * fp)
{
	fseek(fp,0,SEEK_SET);
	char s = fgetc(fp);
	while (s != '\n')
	{
		s = fgetc(fp);
	}
	int col = ftell(fp) - 1;
	fseek(fp,0,SEEK_END);
	int row = ftell(fp)/(col + 1);
	Maze * m = malloc_maze(row,col);
	fseek(fp,0,SEEK_SET);
	int a = 0;
	int b = 0;
	for (a = 0; a < m -> num_rows; a++)
	{
		for(b=0; b < m -> num_cols;b++)
		{
			m -> cells[a][b] = fgetc(fp);
			if(b == col - 1)
			{
				fgetc(fp);
			}
		}
	}
	return m;
}



bool write_maze(const char* filename, const Maze* maze)
{
	FILE * faker = fopen(filename,"w");
	if (faker == NULL)
	{
		return false;
	}

	fseek(faker,0,SEEK_SET);

	for (int i = 0; i < maze -> num_rows; i++)
	{
		for (int j = 0; j < maze -> num_cols; j++)
		{
			fputc(maze->cells[i][j],faker);
		}
		fputc('\n',faker);
	}
	fclose(faker);
	return true;
}

Maze * make_taller(const Maze * orig)
{
	Maze * taller;
	int i = 0;
	int j = 0;
	int row = 2 * (orig -> num_rows) - 1;
	int col = orig -> num_cols;
	taller = malloc_maze(row,col);
	
	for (i = 0;i < orig -> num_rows;i++)
	{
		for(j = 0;j < orig -> num_cols;j++)
		{
			taller -> cells[i][j] = orig -> cells[i][j];
		}
	}
	for (i = orig -> num_rows; i < taller -> num_rows;i++)
	{
		for (j = 0; j < taller -> num_cols;j++)
		{
			taller->cells[i][j]=orig->cells[(orig->num_rows-1)-(i-(orig->num_rows-1))][j];
		}
	}

	return taller;
}

Maze * make_wider(const Maze * orig)
{
	Maze * wider;
	int i = 0;
	int j = 0;
	int row = orig -> num_rows;
	int col = 2 * (orig -> num_cols) - 1;
	int midrow = (orig -> num_rows) / 2;
	int midcol = (orig -> num_cols) - 1;
	wider = malloc_maze(row,col);
	for (i = 0; i < orig -> num_rows; i++)
	{
		for (j = 0; j < orig -> num_cols; j++)
		{
			wider -> cells[i][j] = orig -> cells[i][j];
		}
	}
	wider -> cells[midrow][midcol] = PATH;
	while (wider -> cells[midrow + 1][midcol] == WALL && wider -> cells[midrow - 1][midcol] == WALL)
	{
		wider -> cells[midrow][midcol - 1] = PATH;
		midcol--;
	}
		for (j = orig -> num_cols; j < col; j++)
		{
			for (i = 0; i < row; i++)
			{
				wider -> cells[i][j] = wider -> cells[i][(orig -> num_cols - 1) - (j - (orig -> num_cols - 1))];
			}
		}
	return wider;
}

