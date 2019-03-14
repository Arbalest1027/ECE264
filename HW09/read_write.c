#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pa09.h"

#ifndef CONNECT

StudentDatabase * ReadDatabase(char * filename) {
	StudentDatabase* db = NULL;
	//TODO 1. Open the file in read and binary format
	FILE * fp = fopen(filename,"rb");
	//TODO 2. Allocate memory for db
	db = malloc(sizeof(StudentDatabase));
	//TODO 3. Find number to entries of Student structure
	int line = 0;
	//char * buffer = malloc(10000*sizeof(char));
	fseek(fp,0,SEEK_SET);
	Student db1;
	while (fread(&db1,sizeof(Student),1,fp)){
	  line++;
	}
	//TODO 4. Set the value of db->number to the number of students
	db -> number = line;
	// TODO 5. Allocate the memory for the db->students structure
	db -> students = malloc(line * sizeof(Student*));
	for (int i = 0;i < line; i++){
	  db -> students[i] = malloc(sizeof(Student));
	}
	//TODO 6. Read the file again from start and assign value to each student in the data base
	fseek(fp,0,SEEK_SET);
	for (int i = 0; i < line; i++){
	  fread(db -> students[i],sizeof(Student),1,fp);
	}
	//close the file
	//free(buffer);
	fclose(fp);
	//return the StudentDatabase
	return db;
}

#endif

#ifndef WRITE_DB
//This function is to write to a file in binary format
int WriteDatabase(char *filename, StudentDatabase * db) {
	//TODO 1. Open the file in write and binary format
  FILE* fp = fopen(filename,"wb");
	//TODO 2. check if the StudentDatabase is not null
  if (db == NULL){
    fclose(fp);
    return 0;
  }
	//TODO 3. write into the file and if not possible return 0
  for (int i = 0; i < db -> number; i++){
    fwrite(db -> students[i],sizeof(Student),1,fp);
  }
  fclose(fp);
  return 1;


}
#endif
