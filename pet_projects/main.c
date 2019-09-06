/**
*	FILE: p1.c 
*
*	DESCRIPTION: Given a binary file with 
*	variable record and field sizes, using 
*   '#' as field delimiter. We wish to process 
*	such file, offering insertion, removal, 
*	hexdumping and compression 
*
*	A view of data disposition in a given binary file:	
*   =======================================================
*   ...< Field # Field # Field # Field # ><Next record>...
*   =======================================================

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
	// wrong usage check
	if (argc < 2 || argc > 4) {
		fprintf(stderr, "Usage: %s <action> [args]\n", argv[0]);
		exit(1);
	}

	// database stream (file must exist)
	FILE *fdb;
	if (!(fdb = fopen("records.bin", "r+b"))) {
		
		// file doesn't exist, creat it	
		fdb = fopen("records.bin", "w+b");
		
		// creat avail list frame
		header_init(fdb);
	}
	

	// action switch
	switch (*argv[1]) {
		case 'i':
		{	
			// insertion file	
			FILE *fin = fopen("insere.bin", "rb");
	
			// rrn control file	
			FILE *frn = fopen("rrn_list.bin", "a+b");
			
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
				int curr_offset = ftell(fdb);
				fwrite(rrn, 3, 1, frn);
				fwrite(&curr_offset, sizeof(int), 1, frn);
	
			} else {
		
				// rrn not given, insert all records 
				while (read_record(fin, buffer)) {
				
					// duplicated rrn?
					char rrn_tmp[3];
					memcpy(rrn_tmp, buffer + 4, 3); 	
					if (check_rrn(frn, rrn_tmp)) {
						fprintf(stderr, "rrn %s not available!\n", rrn_tmp);
					// insert and update rrn control file	
					} else {
						insert_record(buffer, fdb);
						// write record rrn to control file
						fwrite(buffer + 4, 3, 1, frn);
						// get offset returned from isertion and write to control file
						int curr_offset = ftell(fdb);
						fwrite(&curr_offset, sizeof(curr_offset), 1, frn);
						fseek(frn, 0, SEEK_SET);
					}
				}
			}
	
			// close scope file streams
			fclose(fin);
			fclose(frn);
			break;
		}

		case 'r':
		{
			// rrn control file	
			FILE *frn;
			if (!(frn = fopen("rrn_list.bin", "r+b")))
					exit(1); //error, nothing to remove
			
			// rrn of desired record
			char *rrn;
			if (argc == 3) 
				rrn = argv[2];
			else 
				rrn = NULL;
		
			int offset;

			// if a rrn was given
			if (rrn) {
				
				// check if rrn exists 
				if (check_rrn(frn, rrn)) {
					fread(&offset, 4, 1, frn);
					// remove record
					remove_record(fdb, offset);
					// update control file
					remove_rrn(frn);

				} else { exit(1); } 
				
			} else {
				
				// open remove file
				FILE *frm;
				if (!(frm = fopen("remove.bin", "rb")))
					exit(1);

				// remove all rrn listed on file
				char frrn[3];
				while (fread(&frrn, 3, 1, frm)) {
					// if rrn exists proceed with removal
					if (check_rrn(frn, frrn)) {
						fread(&offset, 4, 1, frn);
						// remove record
						remove_record(fdb, offset);
						// update control file
						remove_rrn(frn);
					} else { 
						fprintf(stderr, "rrn %s was not found!\n", frrn);
					}
				
					// skip 00 padding
					fseek(frm, 1, SEEK_CUR);
					// reset control file pointer
					fseek(frn, 0, SEEK_SET);
				}
				fclose(frm);	
			}


			fclose(frn);	
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



