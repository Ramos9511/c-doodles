/**
*	FILE: p1.c 
*
*	DESCRIPTION: Given a binary file
* 	organized as follows,
*
*	A view of data disposition in a given binary file:	
*   ====================================================
*   ...< Field # Field # Field # Field ><Next record>...
*   ====================================================
*
*	with variable record and field 
*	sizes, using '#' as field delimiter. 
*	We wish to process such file, offering 
*	insertion, removal, hexdumping and compression 
*	functionality under the following restraints:  
*
*	- Intensive data manipulations  must be done in 
*     secondary memory, in other words, directily on 
*     file stream.
*
*   - Use as little temporary files as possible  
*
*	AUTHOR: gfvante - 30 August 2019
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
#include <stdlib.h>
#include "record_utils.h"

int main(int argc, char *argv[])
{
	/* TODO: command line args handling...
		
	   - actions:
	   		1 - insertion
			2 - remove
			3 - compress
			4 - dump
			5 - load
			
		- help summary
	*/

	// wrong usage check
	if (argc < 2 || argc > 4) {
		fprintf(stderr, "Usage: %s <action> [args]\n", argv[0]);
		exit(1);
	}

	// database stream (file must exist)
	FILE *fdb;
	if (!(fdb = fopen("records.bin", "r+b")))
		fdb = fopen("records.bin", "w+b");
	
	// creat avail list frame
	header_init(fdb);

	// action switch
	switch (*argv[1]) {
		case 'i':
		{	
			// insertion file	
			FILE *fin = fopen("insere.bin", "rb");
	
			// rrn control file	
			FILE *frn = fopen("rrn_list.txt", "a+");
			
			// main data buffer
			char *buffer = malloc(RECORD_SIZE); 

			// rrn of desired record
			char *rrn;
			if (argc == 3) 
				rrn = argv[2];
			else 
				rrn = NULL;
		
			// if a rrn was given
			if (rrn) {
				
				// duplicated rrn?
				if (check_rrn(frn, rrn)) {
					fprintf(stderr, "rrn %s not available!\n", rrn);
					exit(1);
				}

				// search rrn pos in fin and set stream position
				int rrn_offset = search_rrn(fin, rrn);
				fseek(fin, rrn_offset, SEEK_SET);

				// read, treat and insert record
				read_record(fin, buffer);
				insert_record(buffer, fdb);

				// update rrn control file
				fprintf(frn, "%s\n", rrn);
	
			} else {
		
				// rrn not given, insert all records 
				while (read_record(fin, buffer)) {
				
					// duplicated rrn?
					char rrn_tmp[3];
					memcpy(rrn_tmp, buffer + 4, 3); 	
					if (check_rrn(frn, rrn_tmp)) {
						fprintf(stderr, "rrn %s not available!\n", rrn_tmp);
					} else {
						// insert and update rrn control file	
						insert_record(buffer, fdb);
						fwrite(buffer + 4, 3, 1, frn);
						fprintf(frn, "\n");
						fseek(frn, 0, SEEK_SET);
					}
				}
			}

			fclose(fin);
			break;
		}

		case 'r':
		{	// remove stuff
			break;
		}
		
		case 'c':
		{
			// compress stuff
			break;
		}

		case 'd':
		{
			// dump stuff
			break;
		}

		default:
			fprintf(stderr, "Unknown action: %s\n", argv[1]);
			exit(1);
	}

	/* closing input stream,
	we won't use it anymore */
	fclose(fdb);

}



