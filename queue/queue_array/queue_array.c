/************************************************
*
*   FILENAME: queue_array.c
*
*   DESCRIPTION: Implementation of queue data 
*                structure using static ring 
*                buffers
*
*   Author: gfvante - 15 August 2019
*
*************************************************/

#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 50 

struct queue {
    int queue[MAX_SIZE];
    int head, tail;
} typedef Queue;

Queue *queue_new();
int is_empty(Queue *q);
int peek(Queue *q);
void enqueue(int x, Queue *q);
void dequeue(Queue *q);

// test cases
int main(int argc, char *argv[])
{
    Queue *q = queue_new();
    if (is_empty(q))
        fputs("Queue is empty!\n", stdout);
    enqueue(0, q);
    fprintf(stdout, "Queue head: %d\n", peek(q));
    enqueue(1, q);
    fprintf(stdout, "Queue head: %d\n", peek(q));
    enqueue(2, q);
    fprintf(stdout, "Queue head: %d\n", peek(q));
    enqueue(3, q);
    fprintf(stdout, "Queue head: %d\n", peek(q));
    enqueue(4, q);
    fprintf(stdout, "Queue head: %d\n", peek(q));
    dequeue(q);
    fprintf(stdout, "Queue head: %d\n", peek(q));
    dequeue(q);
    fprintf(stdout, "Queue head: %d\n", peek(q));
    dequeue(q);
    fprintf(stdout, "Queue head: %d\n", peek(q));
    dequeue(q);
    fprintf(stdout, "Queue head: %d\n", peek(q));
    dequeue(q);
}

int is_empty(Queue *q) 
{
    if (q->head == -1 && q->tail == -1)
        return 1;
    else
        return 0;
}

void dequeue(Queue *q)
{
   if (is_empty(q)) {
       fputs("Queue is empty!", stderr);
       exit(EXIT_FAILURE);
   } else if (q->head == q->tail) {
       q->head = q->tail = -1;
   } else {
       q->head = (q->head + 1) % MAX_SIZE;
   }
}

void enqueue(int x, Queue *q)
{
   if ((q->tail + 1) % MAX_SIZE == q->head) {
       fputs("Queue is full!", stderr);
       exit(EXIT_FAILURE);
   } else if (is_empty(q)) {
       q->head = q->tail = 0;
   } else {
       q->tail = (q->tail + 1) % MAX_SIZE;
   }
    q->queue[q->tail] = x;
}

Queue *queue_new()
{
    Queue *q = malloc(sizeof(Queue));
    if (!q) {
        fputs("Out of memory!", stderr);
        exit(EXIT_FAILURE);
    }
        q->tail = q->head = -1;
    return q;
}

int peek(Queue *q)
{
    if (!is_empty(q))
        return q->queue[q->head];
    fputs("Queue is empty!", stderr);
    return -1;
}
