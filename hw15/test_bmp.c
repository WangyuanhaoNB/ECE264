#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

int main()
{
	FILE* fptr = fopen("airplane.bmp","r");
	char* error = NULL;
	if(fptr == NULL)
	{
		printf("File does not exist!\n");
		return EXIT_FAILURE;
	}
	BMPImage* image = read_bmp(fptr,&error);
	if(error != NULL)
	{
		printf("%s",error);
		free(error);
	}
	fclose(fptr);

	fptr = fopen("output_file.bmp","w+");
	if(fptr == NULL)
	{
		printf("File does not exist!\n");
		return EXIT_FAILURE;
	}
	BMPImage* crop = crop_bmp(image,100,100,450,250,&error);
	if(error != NULL)
	{
		printf("%s",error);
		free(error);
	}
	if(write_bmp(fptr,crop,&error) == false)
	{
		if(error != NULL)
		{
			printf("%s",error);
			free(error);
		}
	}
	FILE* message = fopen("expected.txt","w");
	if (message == NULL)
	{
		printf("File does not success!\n");
		return EXIT_FAILURE;
	}
	else
	{
		printf("File success!");
	}
	free_bmp(image);
	free_bmp(crop);
	fclose(fptr);
	fclose(message);

	return EXIT_SUCCESS;
}
