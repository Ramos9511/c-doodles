/**
*	FILE: queue_list.h 
*
*	DESCRIPTION: function prototypes and data
*	definitions of dynamic queue
*	data structure
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

#ifndef __QUEUE_H__
#define __QUEUE_H__

struct Node {
	int data;
	struct Node *next;
} typedef Node;

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
