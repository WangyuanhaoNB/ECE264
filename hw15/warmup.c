#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	int x;
	int y;
}Point;

char* feedback(const char* c)
{
	return strcpy(malloc(sizeof(*c) * (strlen(c) + 1)), c);
}

char* read_file(const char* path,char** error)
{
	FILE* fptr = fopen(path,"r");
	char* output = NULL;
	long file_pos = 0;
	int num = 0;
	if(fptr == NULL)
	{
		if(*error == NULL)
		{
			*error = feedback("File does not exist!\n");
		}
		return output;
	}
	if(fseek(fptr,0,SEEK_END) != 0)
	{
		if(*error == NULL)
		{
			*error = feedback("File cannot be read!\n");
		}
		return NULL;
	}
	file_pos = ftell(fptr);
	if(file_pos == -1)
	{
		if(*error == NULL)
		{
			*error = feedback("File cannot be use!\n");
		}
		return NULL;
	}
	output = (char*)malloc(sizeof(char) * (file_pos + 1));
	if(output == NULL)
	{
		if(*error == NULL)
		{
			*error = feedback("Memory error!\n");
		}
		return NULL;
	}
	if(fseek(fptr,0,SEEK_SET) != 0)
	{
		if(*error == NULL)
		{
			*error = feedback("File cannot be read!\n");
		}
		return NULL;
	}
	num = fread(output,sizeof(char),file_pos,fptr);
	if(num != file_pos)
	{
		if(*error == NULL)
		{
			*error = feedback("Error reading from file\n");
		}
		return NULL;
	}
	output[num] = '\0';
	fclose(fptr);
	return output;
}
void write_file(const char* path,const char* contents,char** error)
{
	FILE* fptr = NULL;
	int i = 0;
	fptr = fopen(path,"w");
	if(fptr == NULL)
	{
		if(*error == NULL)
		{
			*error = feedback("File cannot be made!\n");
		}
		return;
	}
	i = fwrite(contents,sizeof(char),strlen(contents),fptr);
	if(i != strlen(contents))
	{
		if(*error == NULL)
		{
			*error = feedback("File cannot be written!\n");
		}
		return;
	}
	fclose(fptr);
}
void write_point(char* path,Point p,char** error)
{
	FILE* fptr = NULL;
	int axis[] = {p.x,p.y};
	int i = 0;
	fptr = fopen(path,"w");
	if(fptr == NULL)
	{
		if(*error == NULL)
		{
			*error = feedback("File cannot be written!\n");
		}
		return;
	}
	i = fwrite(axis,sizeof(int),2,fptr);
	if(i != 2)
	{
		if(*error == NULL)
		{
			*error = feedback("File cannot be written!\n");
		}
		return;
	}
	fclose(fptr);
}
Point read_point(const char* path,char** error)
{
	FILE* fptr = NULL;
	Point p = {.x = 0, .y = 0};
	fptr = fopen(path,"r");
	if(fptr == NULL)
	{
		if(*error == NULL)
		{
			*error = feedback("File does not exist!\n");
		}
		return p;
	}
	if(fread(&p.x,sizeof(int),1,fptr) != 1)
	{
		if(*error == NULL)
		{
			*error = feedback("File cannot be read!\n");
		}
		return p;
	}
	if(fread(&p.y,sizeof(int),1,fptr) != 1)
	{
		if(*error == NULL)
		{
			*error = feedback("File cannot be read!\n");
		}
		return p;
	}
	fclose(fptr);
	return p;
}
