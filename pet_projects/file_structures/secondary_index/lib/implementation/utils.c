/**
*	FILE: utils.c 
*
*	DESCRIPTION: implementation of generic 
*	utilitary functions
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
#include <stdlib.h>
#include <ctype.h>
#include "utils.h"

// hexdump macro
#define BYTES_PER_LINE 16

void help() 	// ADJUST HELP SUMMARY TO NEW FUNCTIONALITY
{
	/* Description: Prints user help menu */
		fputs(
			"\nName: \n\
\tfdb - file database manager \n\
Synopsis: \n\
\tfdb ACTION [RRN] \n\
Description: \n\
\tsimple file handler toll for concept ilustration, offers insertion, hexdumping, loading and searching by rrn/name operations \n\
Mandatory arguments (actions): \n\
\t-i [RRN] \n\
\t\tinsertion, record RRN or all(in file) if RRN not given \n\
\t-p [RRN] \n\
\t\tsearch primary, search records of [RRN] or all(in file) if RRN not given \n\
\t-s [NAME] \n\
\t\tsearch secondary, search records of [NAME] or all(in file) if NAME not given \n\
\t-d \n\
\t\thexdump", stdout);

}

char *get_arg(int argc, char **argv)
{
	/* Description: get rrn from command line */
	if (argc == 3) 
		return argv[2];
	else 
		return NULL;
}

void hexdump(FILE *f) {
	
	int bytes_read;

	// line-size buffer
	unsigned char chunk[BYTES_PER_LINE]; 

	// reads in chunks of 16 bytes
	while ((bytes_read = fread(chunk, 1, sizeof(chunk), f)) > 0) {

		// print hex value of each char in chunk
		for (int i = 0; i < bytes_read; i++)
			printf("%02X ", chunk[i]);

		if (bytes_read < 16)
			printf("%*c", 2*BYTES_PER_LINE - bytes_read - 1, ' ');

		printf("%s","\t" );


		// print ascii value of each char in chunk
		for (int i = 0; i < bytes_read; i++) {
			
			// print '.' if char isn't printable
			if (isprint(chunk[i]))
				printf("%c ", chunk[i]);
			else
				printf("%c ", '.');

		}
		printf("\n");
	}
	fclose(f);
}

