/***********************************************************************
*
* FILENAME:
*	<filename>
*
* DESCRIPTION :
* 	<short description>
*
* AUTHOR:
* 	WesternSage - <date>
*
***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "../utils/type_definitions.h"
#include "../linked_list/linked_list.h"
#include "../stack/stack_list/stack_list.h"

Node *list_stack_reverse(Node *head);

int main(int argc, char * argv[])
{
	Node *new_list = list_new();
	list_append(0, &new_list);
	list_append(1, &new_list);
	list_append(2, &new_list);
	list_append(3, &new_list);
	list_print(new_list);
	Node *rnew_list = list_stack_reverse(new_list);
	list_print(new_list);
	list_print(rnew_list);

	return 0;
}

Node *list_stack_reverse(Node *head)
{
	Node *temp = head;
	Node *stack = stack_new();
	Node *rlist = list_new();
	while (temp != NULL) {
		stack_push(temp->data, &stack);
		temp = temp->next;
	}

	while (!stack_is_empty(stack)) {
		list_append(stack_top(stack), &rlist);
		stack_pop(&stack);
	}
	return rlist;
}
