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
*	AUTHORS: Gabriel Fioravante, Mayara Barros, 
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
	}

	char *arg = argv[1];

	/*flow switch */
	switch (arg[1]) {

		case 'i': // insertion (only supports rrn, not names)
		{
			FILE *fin = fopen("insere.bin", "rb");
			FILE *frn = fopen("rrn_list.bin", "a+b"); // control file
			FILE *fn = fopen("name_list.bin", "a+b");
			
			char *buffer = malloc(RECORD_SIZE); 
			char *rrn = get_arg(argc, argv); // get rrn from command line

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

				// update name control Field
				char *name;
				int nsize = read_name(fdb, &name);

				fwrite(name, nsize, 1, fn);
				fwrite("#", 1, 1, fn);
				fwrite(&curr_offset, sizeof(int), 1, fn);

				fclose(fin);
				fclose(frn);
				fclose(fn);
				free(name);
				free(buffer);

				return EXIT_SUCCESS;
			} 
					
			// rrn not given, insert all records 
			
			while (read_record(fin, buffer)) {

				char rrn_tmp[3]; memcpy(rrn_tmp, buffer + 4, 3); 	

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

					// update name control Field
					char *name;
					int nsize = read_name(fdb, &name);
					fwrite(name, nsize, 1, fn);
					fwrite("#", 1, 1, fn);
					fwrite(&curr_offset, sizeof(int), 1, fn);
					fseek(fn, 0, SEEK_SET);
					free(name);
				}
			}
	
			fclose(fn);
			fclose(fin);
			fclose(frn);
			free(buffer);
			break;
		}

		case 'p':
		{
			FILE *fdb = fopen("records.bin", "rb");
			FILE *frn = fopen("rrn_list.bin", "rb");
			FILE *fpin = fopen("busca_p.bin", "rb");
			
			char *rrn = get_arg(argc, argv); // get rrn from command line
					
			int offset;
			if (rrn) {

				// does it exist? 
				if (check_rrn(frn, rrn)) {

					fread(&offset, 4, 1, frn);

					//get record size
					int rsize;
					fseek(fdb, offset, SEEK_SET);
					fread(&rsize, 4, 1, fdb);

					printf("Record size: %d\n", rsize);

					// read and print record
					char *buffer = malloc(rsize);
					fread(buffer, rsize, 1, fdb);
					buffer[rsize - 5] = '\0';
					printf("%s\n", buffer);

				} else { 

					fprintf(stderr, "rrn %s was not found!\n", rrn);
					exit(1); 
				}

			// search all codes in file
			} else {

				char tmp[3];
				while (fread(tmp, 3, 1, fpin)) {

					// does it exist? 
					if (check_rrn(frn, tmp)) {

						fread(&offset, 4, 1, frn);

						//get record size
						int rsize;
						fseek(fdb, offset, SEEK_SET);
						fread(&rsize, 4, 1, fdb);

						// read and print record
						char *buffer = malloc(rsize);
						fread(buffer, rsize, 1, fdb);
						buffer[rsize - 5] = '\0';
						printf("%s\n", buffer);

					} else { 
						fprintf(stderr, "rrn %s was not found!\n", tmp);
						exit(1); 
					}

					fseek(fpin, 1, SEEK_CUR); // skip '\0'
					fseek(frn, 0, SEEK_SET); // skip '\0'				
				}
			}

			fclose(fdb);
			fclose(frn);

			return EXIT_SUCCESS;	 
		}

		case 's':
		{
			FILE *fdb = fopen("records.bin", "rb");
			FILE *fn = fopen("name_list.bin", "rb");
			FILE *fsin = fopen("busca_s.bin", "rb");
			
			char *name = get_arg(argc, argv); // get name from command line
					
			int offset;
			if (name) {

				// does it exist? 
				if (check_name(fn, name)) {

					// check_name should match name and 
					// position file pointer at offset
					fread(&offset, 4, 1, fn);

					//get record size
					int rsize;
					fseek(fdb, offset, SEEK_SET);
					fread(&rsize, 4, 1, fdb);

					printf("size: %d\n", rsize);

					// read and print record
					char *buffer = malloc(rsize);
					fread(buffer, rsize, 1, fdb);
					buffer[rsize - 5] = '\0';
					printf("%s\n", buffer);
					free(buffer);

				} else { 
					fprintf(stderr, "%s was not found!\n", name);
					exit(1); 
				}

			// search all given names
			} else {

				char c;
				int nmsize = 0, latch = 0;

				while (fread(&c, 1, 1, fsin)) {

					if (isprint(c)) {
						if (latch) latch = 0;
						nmsize++;
					} else {

						if (!latch) {
							// reads name into buffer
							fseek(fsin, -(nmsize+1), SEEK_CUR);
							char *name_in = malloc(nmsize); 
							fread(name_in, nmsize, 1, fsin);

							// print records

							// does it exist? 
							if (check_name(fn, name_in)) {

							// check_name should match name and 
							// position file pointer at offset
							fread(&offset, 4, 1, fn);

							//get record size
							int rsize;
							fseek(fdb, offset, SEEK_SET);
							fread(&rsize, 4, 1, fdb);

							// read and print record
							char *buffer = malloc(rsize);
							fread(buffer, rsize, 1, fdb);
							buffer[rsize - 5] = '\0';
							printf("%s\n", buffer);

							fseek(fn, 0, SEEK_SET);

							} else { 
								fprintf(stderr, "%s was not found!\n", name);
							}	

							nmsize = 0;

							free(name_in);
							latch = 1;
						}
					}
				}
			}

			fclose(fdb);
			fclose(fn);
			fclose(fsin);
			return EXIT_SUCCESS;

			break; 
		}

		case 'd': // hexdump
		{
			hexdump(fdb);	
			break;
		}

		case 'h': // help
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

