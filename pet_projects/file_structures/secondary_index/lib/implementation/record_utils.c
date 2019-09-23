/**
*	FILE: record_utils.c 
*
*	DESCRIPTION: Implementation of api functions
*	for management of record files using avail list 
* 
*	AUTHORS: Gabirel Fioravante, Mayara Barros, 
*	Vinicius Noriyuki - 30 August 2019
*
*   NOTE ======================================== 
*   Error handling has not been implemented 
*   for clarity purposes. If you plan on using 
*   this code as part of a real application you 
*   you should treat the possible error scenarios! 
*   ==============================================
*
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "record_utils.h"

void header_init(FILE *fdb)
{
	/* Description: Set up avail 
	   list frame on empty record
	   file */

	fseek(fdb, 0, SEEK_SET);
	int offset = -1;
	fwrite(&offset, sizeof(offset), 1, fdb);
	fseek(fdb, 0, SEEK_SET);
}

void compress(FILE *fdb, FILE *frn) {

	/* Description: gets rid of fragmentation
	   by copying only active records to temporary
	   file, deleting old db file and setting temp
	   as new db */
	
	FILE *fco = fopen(".compression_buffer.bin", "w");
	header_init(fco);
	fseek(fco, 4, SEEK_SET);

	char c;
	while (fread(&c, 1, 1, frn)) {
		
		if (isdigit(c)) {
			// get offset
			int offset;
			fseek(frn, 2, SEEK_CUR); // skipt rrn
			fread(&offset, sizeof(offset), 1, frn);

			// go to begining of record in fdb
			fseek(fdb, offset, SEEK_SET);

			// get record size	
			int rsize;
			fread(&rsize, sizeof(rsize), 1, fdb);
			fseek(fdb, -sizeof(rsize), SEEK_CUR);
	
			// tmp buffer to hold record
			char *buffer = malloc(rsize);

			// copy record from fdb to buffer
			fread(buffer, rsize, 1, fdb);
			
			// copy from buffer to tmp file
			fwrite(buffer, rsize, 1, fco);

			// free buffer
			free(buffer);
		} 
	}

	// swap old db file for compressed version
	fclose(frn);
	fclose(fco);
	fclose(fdb);
	remove("records.bin");
	rename(".compression_buffer.bin", "records.bin");

	/* adjust index offsets since db has changed */
	fdb = fopen("records.bin", "rb");
	frn = fopen("rrn_list.bin", "wb"); // control file
	fseek(fdb, 4, SEEK_SET);

	char cc;
	for (;;) {
		// get offse to recrod
		int offset = ftell(fdb);
		// get record size
		int rsize;
		if(!fread(&rsize, sizeof(rsize), 1, fdb))
			break; // file pointer went past EOF
		// get rrn
		char rrn[3];
		fread(rrn, 3, 1, fdb);
		if (rrn[0] != '*') {
			// write info to control file
			fwrite(rrn, 3, 1, frn);
			fwrite(&offset, sizeof(offset), 1, frn);
		}
		// positioning pointer to next record
		fseek(fdb, rsize - 7, SEEK_CUR);
	}
}

void insert_record(char *record, FILE *fdb)
{
	/* Description: insert new record 
	   at end of file */

	// get record size <-- read int from buffer (4 bytes)
	int rsize = *((int*)record);

	// insert at eof 
	fseek(fdb, 0, SEEK_END);
	fwrite(record, rsize, 1, fdb);

	// position file pointer where it
	// was before insertion
	fseek(fdb, -rsize, SEEK_CUR); 
}

void remove_record(FILE *fdb, int rrn_offset)
{
	/* Description: Given a record offset,
	   mark it as removed and update avail 
	   list with new available space */ 

	// get first avail pos from header
	fseek(fdb, 0, SEEK_SET);

	int offset;
	fread(&offset, sizeof(offset), 1, fdb);

	// insert new position at beginning of list
	fseek(fdb, -sizeof(offset), SEEK_CUR);
	fwrite(&rrn_offset, sizeof(rrn_offset), 1, fdb);

	// link new avail pos to list tail
	fseek(fdb, rrn_offset + 4, SEEK_SET);
	fputc('*', fdb);
	fwrite(&offset, sizeof(offset), 1, fdb);
}


