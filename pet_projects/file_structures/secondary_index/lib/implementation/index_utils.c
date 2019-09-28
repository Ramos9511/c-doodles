/**
*	FILE: index_utils.c 
*
*	DESCRIPTION: Implementation of functions
*	for handling internal rrn index file 
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
#include "index_utils.h"

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

int check_name(FILE *fn, char *name)
{
	/* Description: Search for 
   	   given name  in name
   	   control file */

	char c;
	int i = 0, no_match = 0, nsize;

	while (fread(&c, 1, 1, fn)) {

		if (c == '#') {
			
			if (!no_match && i == strlen(name))
				return 1;

			i = 0;
			no_match = 0;
			fseek(fn, 4, SEEK_CUR);
			continue;
		}

		if (i > strlen(name) || c != name[i])
			no_match = 1;

		i++;
	}

	return 0;

}

