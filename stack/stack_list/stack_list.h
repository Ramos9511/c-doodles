/***********************************************************************
*
* FILENAME:
*	stack_list.h
*
* DESCRIPTION :
* 	Stack api functions prototypes
*	and required data structures (e.g. Node)
*
* AUTHOR:
* 	WesternSage - 06 Augus 2019
*
***********************************************************************/

#ifndef __STACK_H__
#define __STACK_H__

#include <stdbool.h>
#include "../../utils/type_definitions.h"

// TODO : Implement is_empty func

Node *stack_new();
int stack_top(Node *head);
void stack_pop(Node **head);
bool stack_is_empty(Node *head);
void stack_push(int x, Node **head);

#endif
