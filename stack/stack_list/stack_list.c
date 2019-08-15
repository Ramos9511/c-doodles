/*************************************************
*
* FILENAME: stack_list.c
*
* DESCRIPTION: Implementation of stack api 
*              functions using linked lists
*
* AUTHOR: gfvante - 06 August 2019
*
*************************************************/

#include "stack_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

Node *stack_new()
{
    return NULL;
}

bool stack_is_empty(Node *head)
{
    return head == NULL;
}

void *stack_top(Node *head)
{
    return head->data;
}

void stack_pop(Node **head)
{
    if (*head == NULL) return;
    Node *temp = *head;
    *head = (*head)->next;
    free(temp);
}

void stack_push(void *x, Node **head)
{
    Node *new_node = malloc(sizeof(Node));
    if (!new_node) {
        fputs("Out of memory\n", stderr);
        exit(EXIT_FAILURE);
    }
    new_node->data = x;
    new_node->next = *head;
    *head = new_node;
}

