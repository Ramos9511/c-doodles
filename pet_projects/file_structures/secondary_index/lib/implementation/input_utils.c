/**
*	FILE: input_utils.c 
*
*	DESCRIPTION: implementation of functions
*	for handling input files 
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

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "input_utils.h" 

int search_rrn(FILE *fin, char *rrn) 		// shoudl probably rename this to get_offset or something
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

