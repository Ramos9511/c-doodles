/**************************************************
*
* FILENAME: dlinked_list.c
*
* DESCRIPTION : Implementation of doubly Linked
*	            list api functions
*
* AUTHOR: gfvante - 04 August 2019
*
**************************************************/

#include "dlinked_list.h"
#include <stdio.h>
#include <stdlib.h>

Node *dlist_new() {
	return NULL;
}

Node *dlist_new_node(int x)
{
	Node *new_node = malloc(sizeof(Node));
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
