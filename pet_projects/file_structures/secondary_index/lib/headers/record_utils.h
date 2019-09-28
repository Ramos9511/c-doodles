/**
*	FILE: record_utils.h 
*
*	DESCRIPTION: header file for RECORD
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

#define RECORD_SIZE 134
#define FIELDS_PER_RECORD 4

// prototypes
void insert_record(char *record, FILE *fdb);	// insert record at next avail pos
