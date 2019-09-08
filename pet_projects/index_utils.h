/**
*	FILE: index_utils.h 
*
*	DESCRIPTION: Header file of rrn index
*	functions
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

#pragma once
#include <stdio.h>

void remove_rrn(FILE *frn);				// remove rrn entry from index file
int check_rrn(FILE *frn, char *rrn);    // search for rrn in index file

