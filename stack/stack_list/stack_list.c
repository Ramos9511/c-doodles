/***********************************************************************
*
* FILENAME:
*	stack_list.c
*
* DESCRIPTION :
* 	Implementation of stack api functions using
*   linked lists
*
* AUTHOR:
* 	WesternSage - 06 Augus 2019
*
***********************************************************************/

#include "stack_list.h"
#include <stdio.h>
#include <stdlib.h>

Node *stack_new() {
	return NULL;
}

int stack_top(Node *head) {
	return head->data;
}

void stack_pop(Node **head)
{
	if (*head == NULL) return;
	Node *temp = *head;
	*head = (*head)->next;
	free(temp);
}

void stack_push(int x, Node **head)
{
	Node *new_node = (Node*)malloc(sizeof(Node));
	new_node->data = x;
	new_node->next = *head;
	*head = new_node;
}

// test cases
// int main(int argc, char * argv[])
// {
// 	Node *new_stack = stack_new();
// 	stack_push(1, &new_stack);
// 	stack_push(2, &new_stack);
// 	stack_push(3, &new_stack);
// 	printf("%d\n",stack_top(new_stack));
// 	stack_pop(&new_stack);
// 	printf("%d\n",stack_top(new_stack));
// 	stack_pop(&new_stack);
// 	printf("%d\n",stack_top(new_stack));
// 	stack_pop(&new_stack);
// 	printf("%d\n",stack_top(new_stack));
//
// 	return 0;
// }
