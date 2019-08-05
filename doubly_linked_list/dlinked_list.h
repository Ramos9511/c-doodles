/***********************************************************************
*
* FILENAME:
*	dlinked_list.h
*
* DESCRIPTION :
* 	Doubly linked list api functions prototypes
*	and required data structures (e.g. list Node)
*
* AUTHOR:
* 	WesternSage - 05 August 2019
*
***********************************************************************/
#ifndef __DLINKED_LIST_H__
#define __DLINKED_LIST_H__

struct Node {
	int data;
	struct Node *next;
	struct Node *prev;
} typedef Node;

// TODO: Implement append func
// TODO: Implement delete_list func
// TODO: Implement get_node_by_pos func
// TODO: Implement get_node_by_value func
// TODO: Implement remove_by_value func

Node *dlist_new();                      // create new list
Node *dlist_new_node(int x);            // create new node
void dlist_print(Node *head);           // print list
void dlist_rprint(Node *head);          // print list backwards
void dlist_insert(int x, Node **head);  // insert node at head

#endif
