/**
*	FILE: var_record_var_field.c 
*
*	DESCRIPTION: given a binary file
* 	organized as follows,
*
* 	binary-file
*-----------------------------------
*	...
*	<ASCII str[<=15]>
*	<ASCII str[<=15]>
*	<ASCII str[<=26]>
*	<int>
*	...
*----------------------------------
*
*	the file has variable record size,
*	using '|' as field delimiter.
*	We wish to process such a file,
*	printing all of its content in
*	an organized fashion
*
*	AUTHOR: gfvante - 18 August 2019
*
*   NOTE ======================================== 
*   Error handling has not been implemented 
*   for clarity purposes. If you plan on using 
*   this code as part of a real application you 
*   you should treat the possible error scenarios! 
*   ==============================================
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FIELDS_PER_RECORD 4

struct record {
	char *fname;
	char *sname;
	char *address;
	char *number;
} typedef Record;

int main(int argc, char *argv[])
{
	FILE *f = fopen("campo_var_reg_var.dad", "rb");

	// calculating file size in bytes
	fseek(f, 0, SEEK_END);
	long fsize = ftell(f);
	fseek(f, 0, SEEK_SET);

	// loading file into memory    MAYBE TRIM FIRST BYTE DURING LOAD
	char *buffer = malloc(fsize);
	fread(buffer, fsize, 1, f);

	/* calculating number of records
	and declaring vector to hold
	the parsed data */
	int i_delimiters = 0;
	for (int i = 0; i < fsize; i++)
		if (buffer[i] == '|') i_delimiters++;
	int num_of_records = i_delimiters / FIELDS_PER_RECORD;
	Record records[num_of_records];

	/* Tokenize buffer content and load it 
	into structs provind a easy way of
	accessing information */
	char *delimiter = "|";
	char *token = strtok(buffer, delimiter); 
	for (int i = 0; i < num_of_records; i++) {
		records[i].fname = ++token; // trimming first byte of each record
		token = strtok(NULL, delimiter);
		records[i].sname = token;
		token = strtok(NULL, delimiter);
		records[i].address = token;
		token = strtok(NULL, delimiter);
		records[i].number = token;
		token = strtok(NULL, delimiter);
	}
	
	// print all
	for (int i = 0; i < num_of_records; i++) {
		fprintf(stdout, "%s %s %s %s\n", records[i].fname, records[i].sname, 
			records[i].address, records[i].number);
	}

	// print chosen line
	int n = atoi(argv[1]);
	fprintf(stdout, "\n\n%s %s %s %s\n", records[n].fname, records[n].sname, 
		records[n].address, records[n].number); 

	// TMP SECTION =======================

	FILE *ftest = fopen("campo_var_reg_var.dad", "r+t");
	char c;
	while ((c = fgetc(ftest) != EOF))
		fprintf(stdout, "%c ", c);
	free(buffer);
}

