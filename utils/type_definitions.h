/*************************************************
*
* FILENAME: type_definitions.h
*
* DESCRIPTION: Definition of data types used
*              in data structure implementations
*
* AUTHOR: gfvante - 07 August 2019
*
**************************************************/

#ifndef __DATA_TYPES__H__
#define __DATA_TYPES__H__

#include <stdio.h>

struct Node {
	void *data;
	struct Node *next;
} typedef Node;

#endif
