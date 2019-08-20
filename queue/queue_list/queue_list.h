/************************************************
*
*   FILENAME: queue_list.h
*
*   DESCRIPTION: function prototypes and data
				 definitions of dynamic queue
				 data structure
*
*   Author: gfvante - 15 August 2019
*
*************************************************/

#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "type_definitions.h"

struct queue {
	Node *head;
	Node *tail;
} typedef Queue;

// TODO: implement is_empty func

Queue *new();
void peek(Queue *q);
void dequeue(Queue *q);
void enqueue(int x, Queue *q);

#endif
