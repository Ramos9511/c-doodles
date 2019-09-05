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
void header_init(FILE *fdb);					// create avail list frame
int check_rrn(FILE *frn, char *rrn);			// check if given rrn is a duplicate 
int search_rrn(FILE *fin, char *rrn);           // given rrn, return offset to its record
void remove_record(FILE *fdb, int rrn);			// remove record of given rrn
int read_record(FILE *fin, char *record);     	// read single record from insertion file
void insert_record(char *record, FILE *fdb);	// insert record at next avail pos
