/**
*	FILE: queue_list.c 
*
*	DESCRIPTION: Implementation of queue data 
*   structure and api functions using 
*   linked list 
*
*	AUTHOR: gfvante - 20 August 2019
*
*   NOTE ======================================== 
*   Error handling has not been implemented 
*   for clarity purposes. If you plan on using 
*   this code as part of a real application you 
*   you should treat the possible error scenarios! 
*   ==============================================
*
*/

#include <stdio.h>
#include <stdlib.h>
#include "queue_list.h"

Queue *new()
{
	Queue *q = malloc(sizeof(Queue));
	q->head = NULL;
	q->tail = NULL;
	return q;
}

void enqueue(void *x, Queue *q)
{
	Node *n = malloc(sizeof(Node));
	// should check malloc return here...
	n->data = x;
	n->next = NULL;
	if (!q->head && !q->tail) {
		q->head = q->tail = n;
		return;
	}
	q->tail->next = n;
	q->tail = n;
}

void dequeue(Queue *q) 
{
	Node *head = q->head;
	if (!head) return;
	if (q->head == q->tail) {
		q->head = q->tail = NULL;
	} else {
		q->head = q->head->next;
	}
	free(head);
}

int is_empty(Queue *q) 
{
	if (!q->head && !q->tail)
		return 1;
	return 0;
}
	
void *peek(Queue *q) 
{
	return q->head->data;
}
