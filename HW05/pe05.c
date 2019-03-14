#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pe05.h"

//StudentDatabase * Connect(char * filename);
//void Close(StudentDatabase * studb);

StudentDatabase * Connect(char * filename) {
	StudentDatabase * db = NULL;
	int line = 0;
	FILE*  database = fopen(filename,"r");
	if (database == NULL){
	  return NULL;
	}
	fseek(database,0,SEEK_SET);
	int text;
	while(!feof(database)){
	  text = fgetc(database);
	  if  (text == '\n'){
	    line++;
	  }
	}
      	db = malloc(sizeof(StudentDatabase));
	db->students = malloc(line * sizeof(Student*));
	for (int i = 0;i < line;i++){
	  db->students[i] = malloc(sizeof(Student));
	}
	fseek(database,0,SEEK_SET);
	int  _id;
	int  _age;	
	for (int i = 0; i < line; i++){
		fscanf(database,"%d,%[^,],%[^,],%[^,],%[^,],%d\n",&_id,db->students[i]->name,db->students[i]->major,db->students[i]->year,db->students[i]->enrollment,&_age);
		db->students[i]->id = _id;
		db->students[i]->age = _age;

	}
	db->number = line;

	fclose(database);
	return db;
}

#ifndef TEST_CPRNAME
static int CompareByName(const void * s1, const void * s2) {
   Student * a = *(Student**)s1;
   Student * b = *(Student**)s2;
   int k = strcmp(a->name,b->name);
   return (-k);
}
#endif

#ifndef TEST_NAME
void SortDatabaseByName(StudentDatabase * studb) {
	// use qsort to sort the database.
  qsort(studb->students,studb->number,sizeof(Student*),CompareByName);
}
#endif

#ifndef TEST_CPRAGE
static int CompareByAge(const void * s1, const void * s2) {
   Student * a = *(Student**)s1;
   Student * b = *(Student**)s2;
  return (a->age - b->age);
}
#endif

#ifndef TEST_AGE
void SortDatabaseByAge(StudentDatabase * studb) {
	// use qsort to sort the database.
  qsort(studb->students,studb->number,sizeof(Student*),CompareByAge);
}
#endif

#ifndef TEST_WRITE
int WriteDatabase(char *filename, StudentDatabase * db) {
	// Write the info storing in db to filename
  FILE* fp = fopen(filename,"w");
  if (fp == NULL){
    fclose(fp);
    return 0;
  }
  else {
    for (int i = 0; i < db->number; i++){
      fprintf(fp,"ID:%d, Name:%s, Major:%s, Enrollment:%s, Year:%s, Age:%d\n",
	      db->students[i] -> id, db->students[i] -> name, db->students[i] -> major, db->students[i] -> enrollment, db->students[i] -> year, db->students[i] -> age);
    }
  }
  fclose(fp);
  return 1;
}
#endif

void Close(StudentDatabase * studb) {
  for (int i = 0;i < studb->number;i++){
    free(studb->students[i]);
  }
  free(studb->students); 
  free(studb);
}
