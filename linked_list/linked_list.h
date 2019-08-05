/***********************************************************************
*
* FILENAME:
*	linked_list.h
*
* DESCRIPTION :
* 	Linked list api functions prototypes
*	and required data structures (e.g. list Node)
*
* AUTHOR:
* 	WesternSage - 04 Agus 2019
*
***********************************************************************/

#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

struct Node {
	int data;
	struct Node *next;
} typedef Node;

// TODO: Implement append func
// TODO: Implement delete_list func
// TODO: Implement get_node_by_pos func
// TODO: Implement remove by value func
// TODO: Implement get_node_by_value func
// TODO: Separate insert, append and nth-insert funcs

Node *list_new();                               // create empty list
Node *list_new_node(int x);                     // create new list node
void list_print(Node *head);                    // print list
void list_rprint(Node *head);                   // recursive print
void list_rrprint(Node *head);                  // recursive reverse print
void list_reverse(Node **head);                 // revese list
void list_remove(int n, Node **head);           // remove item at pos n
void list_rreverse(Node **head, Node *p);       // recursive reverse
void list_insert(int x, int n, Node **head);    // insert x at pos n

#endif
