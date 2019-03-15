#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include "maze.h"
void free_maze(Maze* );

static bool is_path(Maze *maze, int row, int col){
   if ((row >= 0) && (row < maze->n_row)) {
      if ((col >= 0) && (col < maze->n_col)) {
         return maze->maze_array[row][col] == PATH;
      }
   }
   return false;
}


int _pathfinder_helper(Maze *maze, int curr, int curc,int endr,int endc, int count,int** path,int a,int b, int c, int d){
  if((curr == endr) && (curc == endc)){
    return path[endr][endc];
  }
  if (is_path(maze,curr-1,curc)){
    if (path[curr-1][curc] > count){
      path[curr-1][curc] = count;
      a = _pathfinder_helper(maze,curr-1,curc,endr,endc,count+1,path,a,b,c,d);
    }
  }
  if (is_path(maze,curr+1,curc)){
    if (path[curr+1][curc] > count){
      path[curr+1][curc] = count;
      b = _pathfinder_helper(maze,curr+1,curc,endr,endc,count+1,path,a,b,c,d);
    }
  }
  if (is_path(maze,curr,curc-1)){
    if (path[curr][curc-1] > count){
      path[curr][curc - 1] = count;
      c = _pathfinder_helper(maze,curr,curc-1,endr,endc,count+1,path,a,b,c,d);
    }
  }
  if (is_path(maze,curr,curc+1)){
    if (path[curr][curc + 1] > count){
      path[curr][curc + 1] = count;
      d = _pathfinder_helper(maze,curr,curc+1,endr,endc,count+1,path,a,b,c,d);
    }
  } 
  if (!(a == -1 && b == -1 && c == -1 && d == -1)){
    if (a < count && a != -1){
      count = a;
    }
    if (b < count && b != -1){
      count = b;
    } 
    if (c < count && c != -1){
      count = c;
    } 
    if (d < count && d != -1){
      count = d;
    } 
    int result = path[endr][endc];
    return result;
  }
  else{
    return -1;
  }
}

void _help_print(Maze* maze,int endr,int endc,int count,int** path,FILE* dir_fp){
  fseek(dir_fp,0,SEEK_SET);
  for (int i = count; i > 0;i--){
    if (is_path(maze,endr - 1,endc) && path[endr - 1][endc] == i - 1){
      fputc('S',dir_fp);
      endr--;
    }
    else if (is_path(maze,endr + 1,endc) && path[endr + 1][endc] == i - 1){
      fputc('N',dir_fp);
      endr++;
    }
    else if (is_path(maze,endr,endc + 1) && path[endr][endc + 1] == i - 1){
      fputc('W',dir_fp);
      endc++;
    }
    else if (is_path(maze,endr,endc - 1) && path[endr][endc - 1] == i - 1){
      fputc('E',dir_fp);
      endc--;
    }
  }
}



Maze* malloc_maze(int num_rows, int num_cols){
	Maze *maze = malloc(sizeof(Maze));
	if (maze == NULL){
		free_maze(maze);
		return NULL;
	}
	maze->n_row = num_rows;
	maze->n_col = num_cols;
	maze->maze_array = malloc(num_rows * sizeof(char*));
	for (int i = 0;i < num_rows;i++){
		maze->maze_array[i] = malloc(num_cols * sizeof(char));
	}
	return maze;
}

void free_maze(Maze* maze){
	for (int i = 0;i < maze->n_row;i++){
		free(maze->maze_array[i]);
	}
	free(maze->maze_array);
	free(maze);
}

Maze* read_maze(FILE* fp){
	Maze* maze;
	int num_rows = 0, num_cols = 0;
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
	for(r = 0; r < num_rows; r++){
		for(c = 0;c < num_cols; c++){
			maze->maze_array[r][c] = fgetc(fp);
			if (c == num_cols - 1){
				fgetc(fp);
			}
		}
	}
	return maze;
}

bool write_maze(const char* filename, const Maze* maze){
	FILE * text = fopen(filename,"w");
	if (text == NULL){
		return false;
	}
	fseek(text,0,SEEK_SET);
	for(int i = 0; i < maze->n_row;i++){
		for(int j = 0;j < maze->n_col;j++){
			fprintf(text,"%c",maze->maze_array[i][j]);
		}
		fprintf(text,"\n");
	}
	fclose(text);
	return true;
}	
int dfs_shortest_path_directions(char *maze_file, char *directions_file,
                        Coord source, Coord destination)
{

  FILE* maze = fopen(maze_file,"r");
  FILE* dirc = fopen(directions_file,"w");
  if (maze == NULL || dirc == NULL){
    return -1;
  }
  Maze* maze_cpy = read_maze(maze);
  fclose(maze);
  int** way = malloc(sizeof(int*) * (maze_cpy->n_row));
  for(int i = 0; i < maze_cpy->n_row; i++){
    way[i] = malloc(sizeof(int) * (maze_cpy->n_col));
  }
  for(int j = 0; j < maze_cpy->n_row;j++){
    for(int k = 0;k < maze_cpy->n_col;k++){
      way[j][k] = 1000;
    }
  }
  int a = 0,b = 0,c = 0,d = 0;
  way[source.row][source.col] = 0;
  int count =  _pathfinder_helper(maze_cpy,source.row,source.col,destination.row,destination.col,1,way,a,b,c,d);
  _help_print(maze_cpy,destination.row,destination.col,count,way,dirc);
  for (int l = 0; l < maze_cpy->n_row;l++){
    free(way[l]);
  }
  free(way);
  free_maze(maze_cpy);
  fclose(dirc);
  return count;
}
  
int simulate_movement(char *maze_file, char *directions_file, char *visited_file,
                      Coord source, Coord destination)
{
	FILE* maze = fopen(maze_file,"r");
	if (maze == NULL){
		return -1;
	}
	FILE* dirc = fopen(directions_file,"r");
	if (dirc == NULL){
		return -1;
	}	
	Maze* maze_cpy = read_maze(maze);
	fclose(maze);
	fseek(dirc,0,SEEK_SET);
	char direction = fgetc(dirc);
	int startr = source.row;
	int startc = source.col;
	int count = 1;
	maze_cpy->maze_array[startr][startc] = VISITED;
	while (!feof(dirc)){
	  if (direction == 'N'){
	    maze_cpy->maze_array[startr - 1][startc] = VISITED;
	    startr--;
	  }
	  else if (direction == 'W'){
	    maze_cpy->maze_array[startr][startc - 1] = VISITED;
	    startc--;
	  }
	  else if (direction == 'S'){
	    maze_cpy->maze_array[startr + 1][startc] = VISITED;
	    startr++;
	  }
	  else if (direction == 'E'){
	    maze_cpy->maze_array[startr][startc + 1] = VISITED;
	    startc++;
	  }
	  direction = fgetc(dirc);
	  count++;
	} 
	fclose(dirc);
	free_maze(maze_cpy);
	return count;
}

