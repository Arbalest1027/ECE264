#include <stdio.h>
#include <stdlib.h>
#include "maze.h"

void find_maze_dimensions(FILE * fp, int * a_num_rows, int * a_num_cols) {
   	fseek(fp,0,SEEK_SET);
	*a_num_rows = *a_num_cols = 0; 
   int size = 0;
   while (!feof(fp)){
	   char text = fgetc(fp);
	   if (text == '\n'){
		   *a_num_rows += 1;
       }
	   if (text != EOF && text != '\n'){
		   size++;
	   }
   }	   
   *a_num_cols = size / *a_num_rows;
}

int find_opening_location(FILE * fp) {
	fseek(fp,0,SEEK_SET);
	int location = 0;
	while (fgetc(fp) != PATH){
		location++;
	}	
   return location;
}

int count_path_locations(FILE * fp) {
	fseek(fp,0,SEEK_SET);
	int blank = 0;
	while (!feof(fp)){
		int text = fgetc(fp);
		if (text != EOF){
			if (text == PATH){
				blank++;
				if (text == EOF){
					break;
				}
			}
		}
	}	
   return blank;
}

char get_location_type(FILE * fp, int row, int col) {
	fseek(fp,0,SEEK_SET);
	int num_row;
	int num_col = 0;
	int location;
	find_maze_dimensions(fp,&num_row,&num_col);
	location = num_col * row + row + col;
	fseek(fp,location,SEEK_SET);
	char text = fgetc(fp);
	return text;
}
 
int represent_maze_in_one_line(char * filename, FILE * fp) {
	int size = 0;
	FILE * charactor = fopen(filename,"w");
	fseek(fp,0,SEEK_SET);
	if (charactor == NULL){
		return MAZE_WRITE_FAILURE;
	}
	int text = fgetc(fp);
	while (!feof(fp)){
		if (text != '\n'){
			fputc(text,charactor);
			size++;
		}
		text = fgetc(fp);
	}
	fclose(charactor);
	return size;
}
