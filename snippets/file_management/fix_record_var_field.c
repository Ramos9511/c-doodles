/**
*	FILE: fix_record_var_field .c
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
*	the file has fixed record size,
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
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#define RECORD_SIZE 60

struct record {
	char *fname;
	char *sname;
	char *address;
	char *number;
} typedef Record;

void get_record(char **buffer, int delimiter, Record *record);

int main (int argc, char *argv[])
{
	FILE *f = fopen("campo_var_reg_fixo.dad", "rb");

	// calculating file size in bytes
	fseek(f, 0, SEEK_END);
	long fsize = ftell(f);
	fseek(f, 0, SEEK_SET);

	/* calculating number of records
	and declaring vector to hold
	the parsed data */
	int num_of_records = fsize/RECORD_SIZE;
	Record records[num_of_records];

	// loading file into memory
	char *buffer = malloc(fsize);
	
	/* Treating file content -  the general idea 
	here is traversing the file one byte at a time, 
	copying it to our memory buffer if it belongs to 
	a valid field. In other words, ignore all bytes 
	(garbage values) found inside a given register 
	after reading all of its four fields by skiping 
	to the next record 

	A view of record disposition in a given input file:	
	===================================================================
	< Field | Field| Field | Field | (garbage values)...><Next record>
	===================================================================*/   

	char c;
	int i_buffer = 0, i_delimiter = 0, i_file = 0, offset;
	while (fread(&c, 1, 1, f)) {
		i_file++;
		if (isprint(c)) buffer[i_buffer++] = c;
		/* keeping track of fiels 
		 by counting delimiters*/
		if (c == '|') i_delimiter++;
		/* check if we are in a 'garbage zone' */
		if (!(i_delimiter % 4) && i_delimiter) {
			// jumping to the next record
			offset = RECORD_SIZE - (i_file % RECORD_SIZE) - 1;
			fseek(f, offset, SEEK_CUR);
			// adjusting file position index
			i_file += offset;  
			i_delimiter = 0;
		}
	}

//	buffer[fsize] = '\0';
	
	/* Tokenize buffer content and load it 
	into structs provind a easy way of
	accessing information */
	char *delimiter = "|";
	char *token = strtok(buffer, delimiter); 
	for (int i = 0; i < num_of_records; i++) {
		records[i].fname = token;
		token = strtok(NULL, delimiter);
		records[i].sname = token;
		token = strtok(NULL, delimiter);
		records[i].address= token;
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

	free(buffer);
}

