/**
*	FILE: t2.c
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
*/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#define  RECORD_SIZE 60

struct record {
	char *fname;
	char *sname;
	char *address;
	char *number;
} typedef Record;

void get_fields(char *buffer, char *delimiter, Record *record);

int main (int argc, char *argv[])
{
	int n = atoi(argv[1]);
	FILE *f = fopen("campo_var_reg_fixo.dad", "rb");

	// calculating file size in bytes
	fseek(f, 0, SEEK_END);
	long fsize = ftell(f);
	fseek(f, 0, SEEK_SET);

	Record records[fsize/RECORD_SIZE];

	// loading file into memory
	char *buffer = malloc(fsize);

	// treating and loading data into memory
	char c;
	
	/* the general idea here is traversing the file
	   one byte at a time, copying it to our memory
	   buffer if it belongs to a valid field. In other 
	   words, ignore all bytes (garbage values) found 
	   inside a given register after reading all of its 
	   four fields by skiping to the next record */   

	int i_buffer = 0, i_delimiter = 0, i_file = 0, offset;
	while (fread(&c, 1, 1, f)) {
		i_file++;
		buffer[i_buffer++] = c;
		/* keeping track of fiels 
		 by counting delimiters*/
		if (c == '|') i_delimiter++;
		/* check if we are in a 'garbage zone' */
		if (!(i_delimiter % 4) && i_delimiter) {
			// skiping to the next record
			offset = RECORD_SIZE - (i_file % RECORD_SIZE) - 1;
			fseek(f, offset, SEEK_CUR);
			i_file += offset; // adjusting  file position index 
			i_delimiter = 0;
		}
	}

	/* Tokezine buffer contents and 
	store it in a vector for easy access */

	for (int i = 0; i < fsize; i++) {
		fprintf(stdout, "%c", buffer[i]);
		fprintf(stdout, "%s %s %s %s\n", records[i].fname,
			records[i].sname, records[i].address,
			records[i].number);
	}
	
}

