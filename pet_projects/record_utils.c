/**
*	FILE: record_utils.c 
*
*	DESCRIPTION: Implementation of api functions
*	declared in record_utils.h header file 
* 
*	AUTHOR: gfvante - 31 August 2019
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
#include <string.h>
#include "record_utils.h"

void help()
{
	fputs(
			"Name: \n
			\t	fdb - file database manager \n
			Synopsis:
			\t	fdb ACTION [RRN] \n
			Description











}


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

void remove_rrn(FILE *frn)
{
	/* Description: remove rrn entry
	   from rrn control file */

	// move pointer to beginning of entry
	fseek(frn, -7, SEEK_CUR); 

	// remove rrn entry
	char blank[7] = {'\0'};			// 8 is size of rrn entry in control file
	fwrite(blank, sizeof(blank), 1, frn); 
}

int check_rrn(FILE *frn, char *rrn)
{
	/* Description: Search for 
	   given rrn number in rrn
	   control file */

	char tmp[3];
	while (fread(tmp, 3, 1, frn)) {

		// return if duplicate
		if (memcmp(tmp, rrn, 3) == 0)
			return 1; 
		
		fseek(frn, 4, SEEK_CUR);
	}

	return 0;
}

int search_rrn(FILE *fin, char *rrn)
{
	/* Description: Search fin for
	   given rrn, returning an offset
	   to its respective record */

	// get number of records 
	fseek(fin, 0, SEEK_END);
	int nrecords = ftell(fin) / RECORD_SIZE;
	fseek(fin, 0, SEEK_SET);

	// search record 
	for (int i = 0; i < nrecords; i++) {

		// load rrn in memory
		char rrn_byte[3];
		fread(rrn_byte, 3, 1, fin);
		fseek(fin, -3, SEEK_CUR);

		// check rrn match and return offset
		if (memcmp(rrn_byte, rrn, 3) == 0) {
			int offset = ftell(fin);
			fseek(fin, 0, SEEK_SET);
			return offset;
		}

		// go to next record
		fseek(fin, 134, SEEK_CUR);
	}

	// rrn not found!
	fseek(fin, 0, SEEK_SET);
	return -1;
}

int read_record(FILE *fin, char *record)
{
	/* Description: traverse the input file
	   one byte at a time, copying it over to
	   'record' memory buffer while skiping all
	   garbage bytes (e.g. 00 compiler padding). */

	char c;
	int dflag = 1;
	int i_buffer = 4;
	int i_delimiter = 0;
	int return_check;

	while (return_check = fread(&c, 1, 1, fin)) {

		if (!return_check) return 0; // check for EOF

		/* Latching flag system - Copy printable
		caracters to record buffer, adding one
		'#' delimiter every time a non-printable
		character immediatly preceded by a printable 
		one is found */
	
		if (isprint(c)) {
			record[i_buffer++] = c;
			if (dflag) dflag = 0; 		// reset flag
		} else {
			// end of field?
			if (!dflag) {
				dflag = 1;
				i_delimiter++;
				record[i_buffer++] = '#';
			}
		}

		// if a whole record was read
		if (i_delimiter == FIELDS_PER_RECORD) {
			// write record size to buffer
			i_buffer;
			// this might be a problem on big endian plataforms
			memcpy(record, &i_buffer, sizeof(i_buffer));
			return 1;
		}
	}
}

void insert_record(char *record, FILE *fdb)
{
	/* Description: insert new record 
	   at first large enough avail pos */

	// position stream back on header
	fseek(fdb, 0, SEEK_SET);

	// get record size <-- read int from buffer (4 bytes)
	int rsize = *((int*)record);

	// get first avail pos
	int offset, offset_prev = 0;
	fread(&offset, sizeof(offset), 1, fdb);

	while (offset != -1) {
		
		fseek(fdb, offset, SEEK_SET);

		// check size of avail pos
		int psize;
		fread(&psize, sizeof(psize), 1, fdb);

		if (psize >= rsize) {
			// get next avail pos offset
			int offset_next;
			fseek(fdb, 1, SEEK_CUR);
			fread(&offset_next, sizeof(offset_next), 1, fdb);
		
			// first avail pos 
			if (!offset_prev) {
				// update header	
				fseek(fdb, 0, SEEK_SET);
				fwrite(&offset_next, sizeof(offset_next), 1, fdb);	
			// some avai pos at the middle 
			} else {
				// update avail list
				fseek(fdb, offset_prev + 5, SEEK_SET);
				fwrite(&offset_next, sizeof(offset_next), 1, fdb);	
			}

			// insert record
			fseek(fdb, offset, SEEK_SET);
			//fseek(fdb, 4, SEEK_CUR);
			fwrite(record, rsize, 1, fdb);
			fseek(fdb, offset, SEEK_SET);
			return;
		}

		// go to next avail pos
		fseek(fdb, 1, SEEK_CUR);
		// keep prev offset to update list
		offset_prev = offset;	
		fread(&offset, sizeof(offset), 1, fdb);
	}

	// no avail pos, just insert at eof 
	fseek(fdb, 0, SEEK_END);
	fwrite(record, rsize, 1, fdb);
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
	
	printf("offset value at time reading: %d\n", offset);

	// insert new position at beginning of list
	fseek(fdb, -sizeof(offset), SEEK_CUR);
	fwrite(&rrn_offset, sizeof(rrn_offset), 1, fdb);

	// link new avail pos to list tail

	printf("offset value at time of writting: %d\n", offset);

	fseek(fdb, rrn_offset + 4, SEEK_SET);
	fputc('*', fdb);
	fwrite(&offset, sizeof(offset), 1, fdb);
}
















