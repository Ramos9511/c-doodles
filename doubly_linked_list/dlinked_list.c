/***********************************************************************
*
* FILENAME:
*	dlinked_list.c
*
* DESCRIPTION :
* 	Implementation of doubly Linked
*	list api functions
*
* AUTHOR:
* 	WesternSage - 04 Agus 2019
*
***********************************************************************/

#include "dlinked_list.h"
#include <stdio.h>
#include <stdlib.h>

Node *dlist_new() {
	return NULL;
}

Node *dlist_new_node(int x)
{
	Node *new_node = (Node*)malloc(sizeof(Node));
	new_node->data = x;
	new_node->prev = NULL;
	new_node->next = NULL;
	return new_node;
}

// insert node at head
void dlist_insert(int x, Node **head)
{
	Node *new_node = dlist_new_node(x);
	if (*head == NULL) {
		*head = new_node;
		return;
	}
	(*head)->prev = new_node;
	new_node->next = *head;
	*head = new_node;
}

void dlist_print(Node *head)
{
	Node *temp = head;
	while (temp) {
		printf("%d ", temp->data);
		temp = temp->next;
	}
}

void dlist_rprint(Node *head)
{
	Node *temp = head;
	if (temp == NULL) return;
	// moving to last node
	while (temp->next != NULL)
		temp = temp->next;
	// moving backwards
	while (temp != NULL) {
		printf("%d ", temp->data);
		temp = temp->prev;
	}
}

// /* test cases */
// int main(int argc, char * argv[])
// {
// 	Node *head = dlist_new();
// 	dlist_insert(2, &head);
// 	dlist_print(head);
// 	printf("\n");
// 	dlist_rprint(head);
// 	printf("\n");
// 	dlist_insert(4, &head);
// 	dlist_print(head);
// 	printf("\n");
// 	dlist_rprint(head);
// 	printf("\n");
// 	dlist_insert(6, &head);
// 	dlist_print(head);
// 	printf("\n");
// 	dlist_rprint(head);
//
// 	return 0;
// }
