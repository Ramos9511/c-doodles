/**
*	FILE: utils.c 
*
*	DESCRIPTION: utilitary functions header 
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

void help();							// print help menu
void hexdump(FILE *f);					// hexadecimal dump of give file
char *get_rrn(int argc, char **argv);   // get rrn arg from command line

