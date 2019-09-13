/**
* 	FILENAME: stack_list.h
*
* 	DESCRIPTION: Stack api functions prototypes
*	and required data structures (e.g. Node)
*
* 	AUTHOR: gfvante - 06 August 2019
*
*   NOTE ====================================== 
*   Error handling has not been implemented 
*   for clarity purposes. If you plan on using 
*   this code as part of a real application you 
*   you should implement it! 
*   ===========================================
*/

#ifndef __STACK_H__
#define __STACK_H__

#include <stdbool.h>

struct Node {
	void *data;
	struct Node *next;
} typedef Node;

Node *stack_new();
void *stack_top(Node *head);
void stack_pop(Node **head);
bool stack_is_empty(Node *head);
void stack_push(void *x, Node **head);

#endif
