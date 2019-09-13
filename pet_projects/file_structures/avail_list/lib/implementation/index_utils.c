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

