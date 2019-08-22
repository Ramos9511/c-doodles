/**
*	FILE: fix_record_fix_field.c
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
*	the file has fixed field and record
*   sizes, we wish to process such a file
*	and print all of its content in
*	an organized fashion
*
*	AUTHOR: gfvante - 18 August 2019
* 
*   NOTE ====================================== 
*   Error handling has not been implemented 
*   for clarity purposes. If you plan on using 
*   this code as part of a real application you 
*   you should implement it! 
*   ===========================================
*/

#include <stdio.h>
#include <stdlib.h>
#define NAME_SIZE 15
#define ADDRESS_SIZE 26

struct record {
	char fname[NAME_SIZE];
	char sname[NAME_SIZE];
	char address[ADDRESS_SIZE];
	int number;
} typedef Record;

int main (int argc, char *argv[])
{
	int n = atoi(argv[1]);
	FILE *f = fopen("fixo.dad", "rb");

	// calculating file size in bytes
	fseek(f, 0, SEEK_END);
	long len = ftell(f);
	fseek(f, 0, SEEK_SET);

	// reading whole file into buffer
	Record records[len/sizeof(Record)];
	fread(records, sizeof(records), 1, f);

	// print content
	for (int i = 0; i < len / sizeof(Record); i++) {
		fprintf(stdout, "%s %s %s %d\n", records[i].fname,
			records[i].sname, records[i].address,
			records[i].number);
	}

	// print line requested by user
	fprintf(stdout, "%s %s %s %d\n", records[n].fname,
			records[n].sname, records[n].address,
			records[n].number);
	
	fclose(f);
}

