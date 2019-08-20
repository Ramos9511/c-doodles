/************************************************
*
*   FILENAME: queue_list.c
*
*   DESCRIPTION: Implementation of queue data 
*                structure using linked list 
*
*   Author: gfvante - 15 August 2019
*
*************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "type_definitions.h"
#include "linked_list.h"

Queue *new()
{
	Queue *q = malloc(sizeof(Queue));
	if (!q) {
		fputs("Out of memory!\n", stderr);
		exit(EXIT_FAILURE);
	}
	q->head = NULL;
	q->tail = NULL;
	return q;
}

void enqueue(int x, Queue *q)
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
	
void peek(Queue *q) 
{
	// should check if queue is empty here...
	fprintf(stdout, "Queue head: %d\n", q->head->data);
}
