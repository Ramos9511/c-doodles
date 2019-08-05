/***********************************************************************
*
* FILENAME:
*		<filename>
*
* DESCRIPTION :
* 		<short description>
*
* AUTHOR:
* 		WesternSage - <date>
*
***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

struct Node {
	int data;
	struct Node *next;
	struct Node *prev;
} typedef Node;

Node *dlist_new_node(int x);
void dlist_print(Node *head);
void dlist_insert(int x, Node **head);

int main(int argc, char * argv[])
{
	printf("%s\n","hello world");

	return 0;
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

}
