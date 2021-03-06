/*
 * test.cpp
 *
 *  Created on: Oct 23, 2017
 *      Author: chelsea
 */
#include "storage.h"
#include "format.h"
#include <iostream>
#include <fstream>


int main() {
	StorageManagement *storage_manager = new StorageManagement();
	char* name="tmp.txt";
	int ret = storage_manager->InitStorage(name);
	if (ret == -1) return ret;
	FILE* fp;
	char buffer[MAX_TUPLE_SIZE+1];
	if ((fp = fopen("supplier.tbl", "r")) == NULL) {
		cout<<"error"<<endl;
		return -1;
	}
	int j = 0;
	while(j<9920) {
	   fgets(buffer, sizeof(buffer), fp);
	   char* input = (char*)calloc(sizeof(char)*MAX_TUPLE_SIZE+1, sizeof(char));
	   char seg[] = "|";
	   char* substr;
	   substr = strtok(buffer, seg);
	   char* part = encode(substr, "int", 5);
	   memcpy(input, part, 5);
	   substr = strtok(NULL, seg);
	   part = encode(substr, "char", 18);
	   strcat(input, part);

	   substr = strtok(NULL, seg);
	   part = encode(substr, "varchar", 100);
	   strcat(input, part);

	   substr = strtok(NULL, seg);
	   part = encode(substr, "int", 3);
	   strcat(input, part);

	   substr = strtok(NULL, seg);
	   part = encode(substr, "char", 15);
	   strcat(input, part);

	   substr = strtok(NULL, seg);
	   part = encode(substr, "float", 15);
	   strcat(input, part);

	   substr = strtok(NULL, seg);
	   part = encode(substr, "varchar", 150);
	   strcat(input, part);

	   for (int i = strlen(input); i < MAX_TUPLE_SIZE; i++)
		   input[i] = '*';
	   input[MAX_TUPLE_SIZE] = '\0';

	   storage_manager->Write(input, MAX_TUPLE_SIZE);
	   j++;
	   free(input);
	}
	fclose(fp);
	char* buf = (char*)malloc(sizeof(char)*PAGE_SIZE);
	int retu = storage_manager->ReadBuffer(81200, buf, PAGE_SIZE);
	if (retu != 0)
	{
		char* final = (char*)calloc(sizeof(char)*MAX_TUPLE_SIZE, sizeof(char));
		final = decode(buf);
		cout<<final<<endl;
		free(final);
	}
	delete storage_manager;
	return 0;
}

