/**
*	FILE: record_utils.h 
*
*	DESCRIPTION: Given the following
*	data disposition in a binary file 
*   of variable record and field size,
*
*	===================================================================
*	< (size)(RRN) # Field # Field # Field # Field >< Next record > ...
*	===================================================================   
*
*	where '(size)' indicates the size of its respective 
*   record (in bytes), this module offers interface routines 
*	to facilitate handling of such files.
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

// input records layout
struct input_record {
	char codigo[4];
	char nome[50];
	char seguradora[50];
	char tipo_seg[30];
} typedef IRecord;

// prototypes
void header_init(FILE *fdb);				    // create avail list frame
void compress(FILE *fdb, FILE *frn);			// compress db file
void remove_record(FILE *fdb, int rrn);			// remove record of given rrn
void insert_record(char *record, FILE *fdb);	// insert record at next avail pos
