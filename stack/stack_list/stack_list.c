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
#include <stdbool.h>

	Node *stack_new() {
		return NULL;
	}

	bool stack_is_empty(Node *head) {
		return head == NULL;
	}

	void *stack_top(Node *head) {
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

//test cases
// int main(int argc, char * argv[])
// {
// 	Node *new_stack = stack_new();
// 	void *n1 = (void*)(malloc(sizeof(int)));
// 	void *n2 = (void*)(malloc(sizeof(int)));
// 	void *n3 = (void*)(malloc(sizeof(int)));
// 	*(int*)n1 = 1;
// 	*(int*)n2 = 2;
// 	*(int*)n3 = 3;
// 	stack_push(n1, &new_stack);
// 	stack_push(n2, &new_stack);
// 	stack_push(n3, &new_stack);
// 	printf("%d\n", *(int*)stack_top(new_stack));
// 	stack_pop(&new_stack);
// 	printf("%d\n", *(int*)stack_top(new_stack));
// 	stack_pop(&new_stack);
// 	printf("%d\n", *(int*)stack_top(new_stack));
// 	stack_pop(&new_stack);
// 	if (stack_is_empty(new_stack))
// 		printf("%s\n", "stack is empty!");
//
// 	return 0;
// }
