#include <stdio.h>
#include <stdlib.h>
#include "maze.h"

Maze* malloc_maze(int num_rows, int num_cols){
	Maze *maze = malloc(sizeof(Maze));
	if (maze == NULL){
	  free_maze(maze);
	  return NULL;
	}
	maze->num_rows = num_rows;
	maze->num_cols = num_cols;
	maze->cells = malloc(num_rows * sizeof(char*));
	for (int i = 0;i < num_rows;i++){
	  maze->cells[i] = malloc(num_cols * sizeof(char));
	}
	return maze;
}

void free_maze(Maze* maze){
	for (int i = 0;i < maze->num_rows;i++){
		free(maze->cells[i]);
	}
	free(maze->cells);
	free(maze);
}

Maze* read_maze(FILE* fp){
	Maze* maze;
	int num_rows = 0,num_cols = 0;
	int r = 0,c = 0;
	char text;
	fseek(fp,0,SEEK_SET);
	int size = 0;

	while (!feof(fp)){
		text = fgetc(fp);
		if (text == '\n'){
			num_rows++;
		}
		if (text != EOF && text != '\n'){
			size++;
		}
	}
	num_cols = size / num_rows;
	maze = malloc_maze(num_rows,num_cols);
	fseek(fp,0,SEEK_SET);
        for (r = 0; r < num_rows;r++){
	  for(c = 0; c < num_cols;c++){
	     maze->cells[r][c] = fgetc(fp);
	     if(c == num_cols - 1){
	       fgetc(fp);
	     }
	  }
	}
	return maze;
}

bool write_maze(const char* filename,const Maze* maze){
  FILE * text = fopen(filename,"w");
  if (text == NULL){
    return false;
  }
  fseek(text,0,SEEK_SET);
  for(int i = 0;i < maze->num_rows;i++){
    for(int j = 0; j < maze->num_cols;j++){   
      fprintf(text,"%c",maze->cells[i][j]);
    }
    fprintf(text,"\n");
  }
  fclose(text);
  return true;
}


Maze* make_taller(const Maze* orig){
  Maze* taller;
  int i = 0,j = 0;
  int num_rows = 2*(orig->num_rows)-1;
  int num_cols = orig->num_cols;
  taller =  malloc_maze(num_rows,num_cols);
  if (taller == NULL){
    free_maze(taller);
    return NULL;
  }
  for (i = 0; i < orig->num_rows; i++){
    for(j = 0; j < orig->num_cols;j++){
      taller->cells[i][j] =  orig->cells[i][j];
    }
  }
  
  for (i = orig->num_rows;i < taller->num_rows;i++){
    for(j = 0; j < taller->num_cols;j++){
      taller->cells[i][j] =  orig->cells[(orig->num_rows - 1) - (i - (orig->num_rows - 1))][j];                   ;
    }      
  }
  return taller;
}


Maze* make_wider(const Maze* orig){
  Maze* maze;
  int i = 0,j = 0;
  int num_rows = orig->num_rows;
  int num_cols = 2*(orig->num_cols)-1;
  maze =  malloc_maze(num_rows,num_cols);
    if (maze == NULL){
    free_maze(maze);
    return NULL;
  }
  for (i = 0; i < orig->num_rows; i++){
    for(j = 0; j < orig->num_cols;j++){
      maze->cells[i][j] =  orig->cells[i][j];
    }
  }
  
    for (j = orig->num_cols;j < num_cols;j++){
    for(i = 0; i < orig->num_rows;i++){
      maze->cells[i][j] =  orig->cells[i][(orig->num_cols - 1) - (j - (orig->num_cols - 1))];                   ;
    }      
  }
    int col = 0;
    int col_mid = (orig->num_cols) - 1;
    int row_mid = (orig->num_rows) / 2;
    j = 1;
    int k = j;
    for (col = col_mid;col > 0; col--){
      if (maze->cells[row_mid - 1][col_mid - j] == PATH || maze->cells[row_mid +1][col_mid - j] == PATH){
	for (;k >= 0;k--){
	  maze->cells[row_mid][col_mid - k] = PATH;
	  maze->cells[row_mid][col_mid + k] = PATH;
	}
	return maze;
      }
       else if (maze->cells[row_mid][col_mid-j] == PATH){
	 for(;k >= 0;k--){
	   maze->cells[row_mid][col_mid-k] = PATH;
	   maze->cells[row_mid][col_mid+k] = PATH;
	}
	return maze;
      }
      else {
	j++;
      }
      }

     return maze;
}
