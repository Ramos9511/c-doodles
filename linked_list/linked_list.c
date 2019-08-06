/***********************************************************************
*
* FILENAME:
*	linked_list.c
*
* DESCRIPTION :
* 	Implementation of Linked list api functions
*
* AUTHOR:
* 	WesternSage - 04 Augus 2019
*
***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

Node *list_new() {
	return NULL;
}

Node *list_new_node(int x)
{
	Node *new_node = (Node*)malloc(sizeof(Node));
	new_node->data = x;
	new_node->next = NULL;
	return new_node;
}

void list_print(Node *head) {
	Node *temp = head;
	while (temp) {
		printf("%d ", temp->data);
		temp = temp->next;
	}
}

// TODO: Implement append func

void list_insert(int x, int n, Node **head)
{
	Node *new_node = list_new_node(x);
	// insertion at first position
	if (n == 1) {
		new_node->next = *head;
		*head = new_node;
	} else {
		Node *temp = (*head);
		for (int i = 0; i < n - 2; i++)
			temp = temp->next;
		new_node->next = temp->next;
		temp->next = new_node;
	}
}

void list_remove(int n, Node **head)
{
	Node *temp = *head;
	// remove first node
	if (n == 1) {
		*head = temp->next;
		free(temp);
	} else {
		for (int i = 0; i < n - 2; i++)
			temp = temp->next;
		Node *temp2 = temp->next;
		temp->next = temp2->next;
		free(temp2);
	}
}

void list_reverse(Node **head)
{
	Node *current = *head;
	Node *prev = NULL;
	Node *next = NULL;
	while (current) {
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	*head = prev;
}

void list_rrprint(Node *head)
{
	if (!head)
		return;
	list_rrprint(head->next);
	printf("%d ", head->data);
}

void list_rprint(Node *head)
{
	if (!head) {
		printf("%d ", head->data);
		return;
	}
	printf("%d ", head->data);
	list_rprint(head->next);
}

void list_rreverse(Node **head, Node *p)
{
	if (p->next == NULL) {
		(*head) = p;
		return;
	}
	list_rreverse(head, p->next);
	Node *q = p->next;
	q->next = p;
	p->next = NULL;
}
