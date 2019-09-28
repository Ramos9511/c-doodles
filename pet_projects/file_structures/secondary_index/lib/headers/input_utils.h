/**
*	FILE: input_utils.h 
*
*	DESCRIPTION: header file for input
*	handler functions
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

// size macros
#define RECORD_SIZE 134
#define FIELDS_PER_RECORD 4

int read_name(FILE *fn, char **name); 					// read the first field (name) from given record pointer
int search_rrn(FILE *fin, char *rrn);		// search fin for rrn, returning offset to record
int read_record(FILE *fin, char *record);   // copy over a treated string of size RECORD_SIZE to buffer


