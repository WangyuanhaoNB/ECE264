#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include "maze.h"

static bool is_path(Maze *maze, int row, int col)
{
   if ((row >= 0) && (row < maze->n_row)) {
      if ((col >= 0) && (col < maze->n_col)) {
         return maze->maze_array[row][col] == PATH;
      }
   }
   return false;
}


static int _pathfinder_helper(Maze *maze, int curr, int curc, int endr, int endc, int count, FILE *dfptr, int** arr, int foundN, int foundS, int foundE, int foundW)
{

   if ((curr == endr) && (curc == endc))
   {
     return arr[endr][endc];
   }

   if (is_path(maze, curr-1, curc)) 
   {

	   if (arr[curr-1][curc] > count)
	   {
		   arr[curr-1][curc] = count;
		   foundN = _pathfinder_helper(maze,curr-1,curc,endr,endc,count+1,dfptr,arr,foundN,foundS,foundE,foundW);
	   }
   }
   if (is_path(maze, curr+1, curc)) 
   {

	   if (arr[curr+1][curc] > count)
	   {
		   arr[curr+1][curc] = count;
		   foundS = _pathfinder_helper(maze,curr+1,curc,endr,endc,count+1,dfptr,arr,foundN,foundS,foundE,foundW);
	   }
   }

   if (is_path(maze, curr, curc+1)) 
   {

	   if (arr[curr][curc+1] > count)
	   {
		   arr[curr][curc+1] = count;
		   foundE = _pathfinder_helper(maze,curr,curc+1,endr,endc,count+1,dfptr,arr,foundN,foundS,foundE,foundW);
	   }
   }

   if (is_path(maze, curr-1, curc)) 
   {

	   if (arr[curr][curc-1] > count)
	   {
		   arr[curr][curc-1] = count;
		   foundW = _pathfinder_helper(maze,curr,curc-1,endr,endc,count+1,dfptr,arr,foundN,foundS,foundE,foundW);
	   }
   }

	
   if (foundN != -1 || foundS != -1 || foundE != -1 || foundW != -1)
   {
	   if (foundN < count && foundN != -1)
	   {
		   count = foundN;
	   }
	   if (foundS < count && foundS != -1)
	   {
		   count = foundN;
	   }
	   if (foundE < count && foundE != -1)
	   {
		   count = foundN;
	   }
	   if (foundW < count && foundW != -1)
	   {
		   count = foundN;
	   }
	   return arr[endr][endc];
   }
   else
   {
	   return -1;
   }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void printpath(Maze* m,int finr, int finc,int finp, int** arr, FILE* direction)
{
	fseek(direction,0,SEEK_SET);
	int i = finp;
	while (i > 0)
	{
		if (is_path(m, finr-1, finc) && arr[finr-1][finc] == i - 1)
		{
			fputc('S',direction);
			finr--;
		}
		else if (is_path(m, finr+1, finc) && arr[finr+1][finc] == i - 1)
		{
			fputc('N',direction);
			finr++;
		}
		else if (is_path(m, finr, finc+1) && arr[finr][finc+1] == i - 1)
		{
			fputc('W',direction);
			finc++;
		}
		else if (is_path(m, finr, finc-1) && arr[finr][finc-1] == i - 1)
		{
			fputc('E',direction);
			finc--;
		}
		i--;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Maze * malloc_maze(int num_rows, int num_cols)
{
  Maze * m = malloc(sizeof(Maze));
  m -> n_row = num_rows;
  m -> n_col = num_cols;
  if(m == NULL)
  {
	  free(m);
	  return NULL;
 }

  m -> maze_array = malloc(sizeof(*(m -> maze_array)) * num_rows);
  if (m -> maze_array == NULL)
  {
	  free(m -> maze_array);
	  free(m);
	  return NULL;
  }

  for (int i = 0; i < num_rows; i++)
  {
	  m -> maze_array[i] = malloc(sizeof(**(m -> maze_array)) * num_cols);
	  if (m -> maze_array[i] == NULL)
	  {
		  free(m -> maze_array[i]);
		  free(m -> maze_array);
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
	for (int i = 0; i < maze -> n_row; i++)
	{
		free(maze -> maze_array[i]);
	}
	free(maze -> maze_array);
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
	for (a = 0; a < m -> n_row; a++)
	{
		for(b=0; b < m -> n_col;b++)
		{
			m -> maze_array[a][b] = fgetc(fp);
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

	for (int i = 0; i < maze -> n_row; i++)
	{
		for (int j = 0; j < maze -> n_col; j++)
		{
			fputc(maze -> maze_array[i][j],faker);
		}
		fputc('\n',faker);
	}
	fclose(faker);
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////

int dfs_shortest_path_directions(char *maze_file, char *directions_file,Coord source, Coord destination)
{
   /* open the file */

   FILE *mfptr = fopen(maze_file, "r");
   if (mfptr == NULL) {
      return -1;
   }
   
   /* read the maze from mfptr */

   Maze *maze = read_maze(mfptr);
   fclose(mfptr);
   if (maze == NULL) {
      return -1;
   }
   int i;
   int j;
   int** arr = malloc(sizeof(int*) * (maze-> n_row));

   for (i = 0; i < maze -> n_row; i++)
   {
	   arr[i] = malloc(sizeof(int) * (maze->n_col));
   }

   for (i = 0; i < maze -> n_row; i++)
   {
	   for(j = 0; j < maze -> n_col; j++)
	   {
		   arr[i][j] = INT_MAX;
	   }
   }

   int curr = source.row;
   int curc = source.col;
   int endr = destination.row;
   int endc = destination.col;
   int foundN = 0;
   int foundS = 0;
   int foundE = 0;
   int foundW = 0;
   int count = 1;
   arr[curr][curc] = 0;

   FILE *direction = fopen(directions_file, "w");
   if (direction == NULL)
   {
	   return -1;
   }
   
   int path = _pathfinder_helper(maze,curr,curc,endr,endc,count,direction,arr,foundN,foundS,foundE,foundW);
   printpath(maze,endr,endc,path,arr,direction);
   for (int d = 0; d < (maze -> n_row); d++)
   {
	   free(arr[d]);
   }
   free(arr);
   free_maze(maze);
   fclose(direction);
   return path;
}

int simulate_movement(char *maze_file, char *directions_file, char *visited_file,Coord source, Coord destination)
{
	FILE* dir = fopen(directions_file,"r");
	FILE* maze = fopen(maze_file,"r");
	fseek(dir,0,SEEK_SET);
	Maze* m = read_maze(maze);
	char s = fgetc(dir);
	int curr = source.row;
	int curc = source.col;
	int count = 1;
	m -> maze_array[curr][curc] = VISITED;
	while (s != EOF)
	{
		if (s == 'N')
		{
			m -> maze_array[curr-1][curc] = VISITED;
			curr--;
		}
		else if (s == 'S')
		{
			m -> maze_array[curr+1][curc] = VISITED;
			curr++;
		}
		else if (s == 'E')
		{
			m -> maze_array[curr][curc+1] = VISITED;
			curc++;
		}
		else if (s == 'W')
		{
			m -> maze_array[curr-1][curc-1] = VISITED;
			curc--;
		}
		s = fgetc(dir);
		count++;
	}
	write_maze(visited_file,m);
	free_maze(m);
	fclose(dir);
	fclose(maze);
	return count;
}
