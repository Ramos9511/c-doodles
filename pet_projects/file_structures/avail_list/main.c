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
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "utils.h"
#include "input_utils.h"
#include "index_utils.h"
#include "record_utils.h"

int main(int argc, char *argv[])
{
	FILE *fdb;
	if (!(fdb = fopen("records.bin", "r+b"))) {
		fdb = fopen("records.bin", "w+b");
		header_init(fdb); // set up avail list frame;
	}

	char *arg = argv[1];

	/*flow switch */
	switch (arg[1]) {
		case 'i':
		{	
			FILE *fin = fopen("insere.bin", "rb");
			FILE *frn = fopen("rrn_list.bin", "a+b"); // control file
			
			char *buffer = malloc(RECORD_SIZE); 
			char *rrn = get_rrn(argc, argv); // get rrn from command line
	
			if (rrn) {
				
				// duplicated rrn?
				if (check_rrn(frn, rrn)) {
					fprintf(stderr, "rrn %s not available!\n", rrn);
					exit(EXIT_FAILURE);
				}

				// search rrn pos in fin and set stream position
				fseek(fin, search_rrn(fin, rrn), SEEK_SET);

				// read, treat and insert record
				read_record(fin, buffer);
				insert_record(buffer, fdb);

				// update rrn control file
				int curr_offset = ftell(fdb);
				fwrite(rrn, 3, 1, frn);
				fwrite(&curr_offset, sizeof(int), 1, frn);

				fclose(fin);
				fclose(frn);
				free(buffer);
				return EXIT_SUCCESS;

			} 
					
			// rrn not given, insert all records 
			
			while (read_record(fin, buffer)) {

				char rrn_tmp[3]; 
				memcpy(rrn_tmp, buffer + 4, 3); 	

				// duplicated rrn?
				if (check_rrn(frn, rrn_tmp)) {
					fprintf(stderr, "rrn %s not available!\n", rrn_tmp);
				} else {
					insert_record(buffer, fdb);
					// write record rrn to control file
					fwrite(buffer + 4, 3, 1, frn);
					// get offset returned and write to control file
					int curr_offset = ftell(fdb);
					fwrite(&curr_offset, sizeof(curr_offset), 1, frn);
					fseek(frn, 0, SEEK_SET);
				}
			}
	
			fclose(fin);
			fclose(frn);
			free(buffer);
			break;
		}
		case 'r':
		{
			FILE *frm = fopen("remove.bin", "rb");
			FILE *frn = fopen("rrn_list.bin", "r+b");
			
			char *rrn = get_rrn(argc, argv); // get rrn from command line
					
			int offset;
			if (rrn) {
				// does it exist? 
				if (check_rrn(frn, rrn)) {
					fread(&offset, 4, 1, frn);
					remove_record(fdb, offset);
					remove_rrn(frn); // update control file
				} else { 
					fprintf(stderr, "rrn %s was not found!\n", rrn);
					exit(EXIT_FAILURE); 
				}

				fclose(fdb);
				fclose(frn);
				return EXIT_SUCCESS;	
			} 
					
			/* rrn not give, remove all */

			char frrn[3];
			while (fread(&frrn, 3, 1, frm)) {

				// if rrn exists proceed with removal
				if (check_rrn(frn, frrn)) {
					fread(&offset, 4, 1, frn);
					remove_record(fdb, offset);
					remove_rrn(frn); // update control file
				} else { 
					fprintf(stderr, "rrn %s was not found!\n", frrn);
				}
				
				fseek(frm, 1, SEEK_CUR); //skip padding
				fseek(frn, 0, SEEK_SET); // reset control file pointer
			}

			fclose(fdb);
			fclose(frn);
			break;
		}
		
		case 'c':
		{
			FILE *frn = fopen("rrn_list.bin", "rb");
			compress(fdb, frn);
			break;
		}

		case 'd':
		{
			hexdump(fdb);	
			break;
		}

		case 'h':
		{
			help();
			break;
		}

		default:
			fprintf(stderr, "Unknown action: %s\n", argv[1]);
			exit(1);
	}
	
	fclose(fdb);
}

