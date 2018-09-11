#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "maze.h"

//int find_path_from_top_entrance_to_bottom_exit(char *maze_file, char *directions_file, char *visited_file);

int main(int argc, char* argv[]) 
{
   if (argc < 2) 
   {
       return EXIT_FAILURE;
   }
  
   if (strcmp("-m", argv[1]) == 0) {
      if (argc != 8) { 
         return EXIT_FAILURE; 
      }
	  char* maze_file = argv[2];
	  char* directions_file = argv[3];
	  Coord source = {.row = atoi(argv[4]),.col = atoi(argv[5])};
	  Coord destination = {.row = atoi(argv[6]),.col = atoi(argv[7])};
	  
      int step_count = dfs_shortest_path_directions(maze_file, directions_file, source, destination);
      printf("%d\n", step_count); 
   } 
   else if (strcmp("-s",argv[1]) == 0)
	{
	   if(argc != 9){
	   return EXIT_FAILURE;
	   }
	   char* maze_file = argv[2];
	   char* directions_file = argv[3];
	   char* visited_file = argv[4];
	   char* c;
	   Coord source = {.row = strtol(argv[5],&c,10),.col = strtol(argv[6],&c,10)};
	   Coord destination = {.row = strtol(argv[7],&c,10),.col = strtol(argv[8],&c,10)};
           if (*c != '\0')
	   {
	     return EXIT_FAILURE;
           }  
           int step_count = simulate_movement(maze_file, directions_file, visited_file, source, destination);	   
	   printf("%d\n",step_count);
	   }
	   else
	   {
      return EXIT_FAILURE;
   }
   return EXIT_SUCCESS;
}
