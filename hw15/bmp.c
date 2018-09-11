#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp.h"

/////////////////////////////////////////////////////////////////////////////////////////////////

void feedback(char** error,char* text)
{
	*error = malloc((strlen(text) + 1) * sizeof(**error));
	strcpy(*error,text);
}

/////////////////////////////////////////////////////////////////////////////////////////////////

BMPImage* read_bmp(FILE* fp,char** error)
{
	BMPHeader start;
	if (fp == NULL)
	{
		feedback(error,"File does not exist!\n");
		return NULL;
	}
	if (fseek(fp,0,SEEK_SET) != 0)
	{
		feedback(error,"File cannot be used!\n");
		return NULL;
	}
	if (fread(&start.type,sizeof(start.type),1,fp) <= 0)
	{
		feedback(error,"'type' cannot be read!\n");
		return NULL;
	}
	if (fread(&start.size,sizeof(start.size),1,fp) <= 0)
	{
		feedback(error,"'size' cannot be read!\n");
		return NULL;
	}
	if (fread(&start.reserved1,sizeof(start.reserved1),1,fp) <= 0)
	{
		feedback(error,"'reserved1' cannot be read!\n");
		return NULL;
	}
	if (fread(&start.reserved2,sizeof(start.reserved2),1,fp) <= 0)
	{
		feedback(error,"'reserved2' cannot be read!\n");
		return NULL;
	}
	if (fread(&start.offset,sizeof(start.offset),1,fp) <= 0)
	{
		feedback(error,"'offset' cannot be read!\n");
		return NULL;
	}
	if (fread(&start.dib_header_size,sizeof(start.dib_header_size),1,fp) <= 0)
	{
		feedback(error,"'dib_header_size' cannot be read!\n");
		return NULL;
	}
	if (fread(&start.width_px,sizeof(start.width_px),1,fp) <= 0)
	{
		feedback(error,"'width_px' cannot be read!\n");
		return NULL;
	}
	if (fread(&start.height_px,sizeof(start.height_px),1,fp) <= 0)
	{
		feedback(error,"'height_px' cannot be read!\n");
		return NULL;
	}
	if (fread(&start.num_planes,sizeof(start.num_planes),1,fp) <= 0)
	{
		feedback(error,"'num_planes' cannot be read!\n");
		return NULL;
	}
	if (fread(&start.bits_per_pixel,sizeof(start.bits_per_pixel),1,fp) <= 0)
	{
		feedback(error,"'bits_per_pixel' cannot be read!\n");
		return NULL;
	}
	if (fread(&start.compression,sizeof(start.compression),1,fp) <= 0)
	{
		feedback(error,"'compression' cannot be read!\n");
		return NULL;
	}
	if (fread(&start.image_size_bytes,sizeof(start.image_size_bytes),1,fp) <= 0)
	{
		feedback(error,"'image_size_bytes' cannot be read!\n");
		return NULL;
	}
	if (fread(&start.x_resolution_ppm,sizeof(start.x_resolution_ppm),1,fp) <= 0)
	{
		feedback(error,"'x_resolution_ppm' cannot be read!\n");
		return NULL;
	}
	if (fread(&start.y_resolution_ppm,sizeof(start.y_resolution_ppm),1,fp) <= 0)
	{
		feedback(error,"'y_resolution_ppm' cannot be read!\n");
		return NULL;
	}
	if (fread(&start.num_colors,sizeof(start.num_colors),1,fp) <= 0)
	{
		feedback(error,"'num_colors' cannot be read!\n");
		return NULL;
	}
	if (fread(&start.important_colors,sizeof(start.important_colors),1,fp) <= 0)
	{
		feedback(error,"'important_colors' cannot be read!\n");
		return NULL;
	}

	BMPImage* image = (BMPImage*)malloc(sizeof(BMPImage));
	if (image == NULL)
	{
		feedback(error,"Image does not exist!\n");
		return NULL;
	}
	if (check_bmp_header(&start,fp) == true)
	{
		image -> header = start;
	}
	else
	{
		feedback(error,"File is not vaild!\n");
		free(image);
		return NULL;
	}
	image -> data = malloc(sizeof(unsigned char) * start.image_size_bytes);
	if (image -> data == NULL)
	{
		feedback(error,"Memory error!\n");
		free(image);
		return NULL;
	}
	int i = 0;
	while (i < start.image_size_bytes)
	{
		if (fread(&image->data[i],sizeof(unsigned char),1,fp) != 1)
		{
			feedback(error,"Cannot store the image!\n");
			free(image -> data);
			free(image);
			return NULL;
		}
		i++;
	}
	return image;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

int check_bit(int bit)
{
	int count = 0;
	while (bit % 4 != 0)
	{
		bit++;
		count++;
	}
	return count;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

bool check_bmp_header(BMPHeader* bmp_hdr,FILE* fp)
{
	if (bmp_hdr -> type != 0x4d42)
	{
		return false;
	}
	if (bmp_hdr -> offset != BMP_HEADER_SIZE)
	{
		return false;
	}
	if (bmp_hdr -> dib_header_size != DIB_HEADER_SIZE)
	{
		return false;
	}
	if (bmp_hdr -> num_planes != 1)
	{
		return false;
	}
	if (bmp_hdr -> compression != 0)
	{
		return false;
	}
	if (bmp_hdr -> num_colors != 0 && bmp_hdr->important_colors != 0)
	{
		return false;
	}
	if (bmp_hdr -> bits_per_pixel != 24)
	{
		return false;
	}
	if (fseek(fp,0,SEEK_END) != 0)
	{
		return false;
	}
	int fileSize = ftell(fp);
	if (fseek(fp,BMP_HEADER_SIZE,SEEK_SET) != 0)
	{
		return false;
	}
	if (fileSize <= 0)
	{
		return false;
	}
	if (((bmp_hdr -> size) != fileSize) && (((bmp_hdr -> image_size_bytes) + (bmp_hdr -> offset)) != fileSize))
	{
		return false;
	}
	int image_size = bmp_hdr->width_px * ((bmp_hdr -> bits_per_pixel) / 8);
	int count = check_bit(image_size);
	image_size = count + image_size;
	image_size = (bmp_hdr -> height_px) * image_size;
	if ((bmp_hdr -> image_size_bytes) != image_size)
	{
		return false;
	}
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool write_bmp(FILE* fp,BMPImage* image,char** error)
{
	if (fp == NULL)
	{
		feedback(error,"File does not exist!\n");
		return false;
	}
	if (image == NULL)
	{
		feedback(error,"write_bmp failed!\n");
		return false;
	}
	int written = fwrite(&(image->header),sizeof(image->header),1,fp);
	if(written != 1)
	{
		feedback(error,"Cannot write the file!\n");
		return false;
	}
	int written2 = fwrite(image->data,sizeof(unsigned char),image->header.image_size_bytes,fp);
	if(written2 != (image->header.image_size_bytes))
	{
		feedback(error,"Cannot write the file!\n");
		return false;
	}

	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void free_bmp(BMPImage* image)
{
	if (image != NULL)
	{
		if (image -> data != NULL)
		{
			free(image -> data);	
			image -> data = NULL;
		}
		free(image);
		image = NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BMPImage* crop_bmp(BMPImage* image, int x, int y, int w, int h, char** error)
{
	BMPImage* crop_image = NULL;
	if (((x+w) > (image->header.width_px)) || ((y+h) > (image->header.height_px)))
	{
		if (*error != NULL)
		{
			free(*error);
		}
		feedback(error, "crop image failed!\n");
		return NULL;
	}
		if (x >= image->header.width_px && y >= image->header.height_px)
		{
			if (x == image->header.width_px && y == image->header.height_px)
			{
				crop_image = NULL;
				return crop_image;
			}
			else
			{
				crop_image = NULL;
				return NULL;
			}
		}
		if (w > image->header.width_px && h > image->header.height_px)
		{
			crop_image = NULL;
			return NULL;
		}
		if (w == x && y == h)
		{
			crop_image = NULL;
			return NULL;
		}
	
	int px = image->header.bits_per_pixel / 8;
	long int image_size = h * w * px + ((4 - ((w * px) % 4))%4) * h;
	long int total_size = image_size + BMP_HEADER_SIZE;
	crop_image = malloc(sizeof(BMPImage));
	crop_image->data = malloc(image_size);
	crop_image->header = image->header;
	crop_image->header.size = total_size;
	crop_image->header.width_px = w;
	crop_image->header.height_px = h;
	crop_image->header.image_size_bytes = image_size;

	unsigned char* new_data = crop_image->data;
	unsigned char* old_data = image->data;
	long int find_start_point = (((image->header.height_px - y - h) * image->header.width_px)+ x) * px + (image->header.height_px - y - h) * ((4 - ((image->header.width_px * px) % 4))%4);
	unsigned char* start_point = &(old_data[find_start_point]);
	long int padding = (((4 - ((image->header.width_px * px) % 4))%4) + (image->header.width_px) * px);
	for (int i = 0; i < h; i++)
	{
		if (i != 0)
		{
			start_point = &(start_point[padding]);
		}
		for (int j = 0; j < (w * px); j++)
		{
			new_data[0] = start_point[j];
			new_data++;
		}
		for (int k = 0; k < ((4 - ((w * px) % 4))%4); k++)
		{
			*new_data = 0x00;
			new_data++;
		}
	}
	return crop_image;
}
