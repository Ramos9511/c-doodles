/**
*	FILE: record_utils.c 
*
*	DESCRIPTION: Implementation of api functions
*	for management of records using index files 
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


