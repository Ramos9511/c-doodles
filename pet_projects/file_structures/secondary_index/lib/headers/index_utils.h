/**
*	FILE: index_utils.h 
*
*	DESCRIPTION: Header file of rrn index
*	functions
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

#pragma once
#include <stdio.h>

int check_rrn(FILE *frn, char *rrn);    // search for rrn in index file
int check_name(FILE *fn, char *name);   // search for name in seconday index file

