#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "pa06.h"
#define MAX_LEN 80

#ifndef TEST_CONSRUCT
/* 
	Construct SelectedField.
	1. This function returns a pointer to SelectedField object.
	2. Allocate memory for SelectedField object.
	3. Initialize all the fields in this object to "false".
	4. return NULL if you fail to allocate memory for SelectedField object.
*/
SelectedField * ConstructField() {
  SelectedField * sf = malloc(sizeof(SelectedField));
  if (sf == NULL){
    return NULL;
  }
  sf->id = false;
  sf->name = false;
  sf->major = false;
  sf->year = false;
  sf->enrollment = false;
  sf->age = false;
  return sf;
}
#endif

#ifndef TEST_PARSE
/* 
	Parse the query and store the information into ParseResult object.
	1. This function returns a pointer to ParseResult object.
	2. The ParseResult object has four fields.
		1. Pointer to SelectedField object. The SelectedField  object stores the informations of which fields are selected in the query. For example, if field id is selected, you should update that field to "true".
		2. Number of condition. 
		3. Array of pointers to Condition object. 
		4. What logic does this query specify. It should be eigther AND or OR.
	3. In this function, you should parse the qeury and store the information to ParseResult object. Similar to `Connect()` function in HW04, you should allocate memory for the required objects and then update the fields in the objects. 
*/
ParseResult * ParseQuery(int num, char ** query) {
  ParseResult * pr = malloc(sizeof(ParseResult));
  int count = 0;
  pr->logic[0] = '\0';
  pr -> condition_num = 0;
  for (count = 0; count < num; count++){
    if (!strcmp(query[count],"AND")){
      pr -> condition_num++;
      strcpy(pr->logic,"AND");
    }
    else if (!strcmp(query[count],"OR")){
      pr -> condition_num++;
      strcpy(pr->logic,"OR");
    }
  }
  pr -> condition_num++;
  pr->conditions = malloc(sizeof(Condition*) * pr->condition_num);
  for (int i = 0;i< pr -> condition_num;i++){
    pr->conditions[i] = malloc(sizeof(Condition));
  }
  pr->field = ConstructField();
  for (int i = 0; i < num; i ++){
    if (!strcmp(query[i],"WHERE")){
      for (int j = 0; j < i; j++){
	if (!strcmp(query[j],"id")){
	  pr->field->id = true;
	}
	else if (!strcmp(query[j],"name")){
	  pr->field->name = true;
	}
       	else if (!strcmp(query[j],"major")){
	  pr->field->major = true;
	}
	else if (!strcmp(query[j],"year")){
	  pr->field->year = true;
	}
	else if (!strcmp(query[j],"enrollment")){
	  pr->field->enrollment = true;
	}
	else if (!strcmp(query[j],"age")){
	  pr->field->age = true;
	}
      }
      for (int k = 0; k < pr -> condition_num; k++){
	strcpy(pr -> conditions[k] -> field,query[i + 1]);
	strcpy(pr -> conditions[k] -> optr,query[i + 2]);
	strcpy(pr -> conditions[k] -> val,query[i + 3]);
	i += 4;
      }
    }
  }
  return pr;
}
#endif


#ifndef TEST_COMPARE
/*
	This is a helper function we provide in this assignment.
	It checks whether a stduent meets the condition.
	You can choose not to use this function.
	Do not modify this function. If you change it, you will get zero.
*/
bool Compare(Student * stu, Condition * condition) {
	if (strcmp(condition -> field, "id") == 0) {
		int id_val = atoi(condition -> val);
		if (strcmp(condition -> optr, "<") == 0) {
			return (stu -> id < id_val);
		} else if (strcmp(condition -> optr, ">") == 0) {
			return (stu -> id > id_val);
		} else if (strcmp(condition -> optr, "=") == 0) {
			return stu -> id == id_val;
		} else if (strcmp(condition -> optr, ">=") == 0) {
			return (stu -> id >= id_val);
		} else if (strcmp(condition -> optr, "<=") == 0) {
			return (stu -> id <= id_val);
		}
	} else if (strcmp(condition -> field, "age") == 0) {
		int age_val = atoi(condition -> val);
		if (strcmp(condition -> optr, "<") == 0) {
			return (stu -> age < age_val);
		} else if (strcmp(condition -> optr, ">") == 0) {
			return (stu -> age > age_val);
		} else if (strcmp(condition -> optr, "=") == 0) {
			return (stu -> age == age_val);
		} else if (strcmp(condition -> optr, ">=") == 0) {
			return (stu -> age >= age_val);
		} else if (strcmp(condition -> optr, "<=") == 0) {
			return (stu -> age <= age_val);
		}
	} else {
		if (strcmp(condition -> field, "name") == 0	) {
			if (strcmp(stu -> name, condition -> val) == 0) {
				return true;	
			}
			return false;	
		} else if (strcmp(condition -> field, "major") == 0 ) {
			if (strcmp(stu -> major, condition -> val) == 0){
				return true;	
			}
			return false;	
		} else if (strcmp(condition -> field, "year") == 0 ) {
			if (strcmp(stu -> year, condition -> val) == 0){
				return true;	
			}
			return false;	
		} else if (strcmp(condition -> field, "enrollment") == 0 ) {
			if (strcmp(stu -> enrollment, condition -> val) == 0){
				return true;	
			}
			return false;	
		}
	} 
	return false;
}
#endif

#ifndef TEST_EXECUTE
/*
	1.This function takes two arguments:
		1. pointer to `StudentDatabase` object.
		2. pointer to `ParseResult` object.	
	2. This function returns a pointer to `ExecuteResult` object.
	3. The `ExecuteResult` object has two fields: First, an array of matched Student's index. Second, length of the array. 
*/
ExecuteResult * ExecuteQuery(StudentDatabase * db, ParseResult * res) {
  ExecuteResult * er = malloc(sizeof(ExecuteResult));
  if (er == NULL){
    return NULL;
  }
  er -> arr = malloc(sizeof(int) * db->number);
  bool tf = 0;
  int l = 0;
  er -> len = 0;
  if (!strcmp(res->logic,"\0")){
    for (int i = 0;i < db -> number;i++){
      for (int j = 0;j < res -> condition_num;j++){
	tf = Compare(db->students[i],res->conditions[j]);
	if (tf == true){
	  er->arr[l] = i;
	  er -> len++;
	  l++;
	}
      }
    }
    return er;
  }
  if (!strcmp(res->logic,"OR")){
    for (int i = 0;i < db -> number;i++){
      for (int j = 0;j < res -> condition_num;j++){
	tf = Compare(db->students[i],res->conditions[j]);
	if (tf == true){
	  er->arr[l] = i;
	  er -> len++;
	  l++;
	}
      }
    }
    return er;
  }
  if (!strcmp(res->logic,"AND")){
    //   printf("%d\n",res -> condition_num);
    // int desi[res->condition_num] = {0};
    int number = 0;
    l = 0;
    er -> len = 0;
    for (int i = 0;i < db -> number;i++){
      number = 0;
      for (int j = 0;j < res -> condition_num;j++){
	tf = Compare(db->students[i],res->conditions[j]);
	if (tf == true){
	  number++;
	}
      }
      if (number == res -> condition_num){
	er->arr[l] = i;
	er -> len++;
	l++;
      }
    }
  }
  return er;
}
#endif

#ifndef TEST_FREEPARSE
/*
	Free the allocated memory in ParseResult object.
*/
void FreeParseResult(ParseResult * res) {
  for (int i = 0; i < res -> condition_num;i++){
    free(res->conditions[i]);
  }
  free(res -> conditions);
  free(res -> field);
  free(res);
}
#endif

#ifndef TEST_FREEEXECUTE
/*
	Free the allocated memory in ExecuteResult object.
*/
void FreeExecuteResult(ExecuteResult * res) {
  free(res -> arr);
  free(res);
}
#endif

#ifndef TEST_WRITE

/*
	1. Only write selected fields of students who meet specified conditions to output file.
	2. Print error message "Failed to open file\n" to monitor if the fopen fail. You should not have output file generated if fopen fail. 
	3. Follow this format "field:%s ", or "field:%d ". Add "\n" when you finish writing the selected fileds of a student. Please look at the files in `expected` folder to make sure you understand the format. We will use diff to test. Make sure your output format is correct.
	4. You should write the info of each student in the following order if that fields are selected. id -> name -> major -> year -> enrollment -> age.
	5. The order in selected fields does not affect the order you write to the file.  e.g., `SELECT id name WHERE ...` and `SELECT name id WHERE ...` should have the same output file.  
*/
void WriteDb(StudentDatabase * db, SelectedField * info, ExecuteResult * execute_res, char * filename) {
  FILE* op = fopen(filename,"w");
  if (op == NULL){
    printf("Fail to open file\n");
    return;
  }
  for (int i = 0;i < execute_res->len;i++){
    if (info->id == true){
      fprintf(op,"id:%d ",db->students[execute_res->arr[i]]->id);
    }
    if (info->name == true){
      fprintf(op,"name:%s ",db->students[execute_res->arr[i]]->name);
    }
    if (info->major == true){
      fprintf(op,"major:%s ",db->students[execute_res->arr[i]]->major);
    }
    if (info->year == true){
      fprintf(op,"year:%s ",db->students[execute_res->arr[i]]->year);
    }
    if (info->enrollment == true){
      fprintf(op,"enrollment:%s ",db->students[execute_res->arr[i]]->enrollment);
    }
    if (info->age == true){
      fprintf(op,"age:%d ",db->students[execute_res->arr[i]]->age);
    }
    fprintf(op,"\n");
  }
  fclose(op);
  
}

#endif

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

void Close(StudentDatabase * studb) {
  for (int i = 0;i < studb->number;i++){
    free(studb->students[i]);
  }
  free(studb->students); 
  free(studb);
}
