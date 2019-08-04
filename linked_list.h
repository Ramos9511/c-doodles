/***********************************************************************
*
* FILENAME:
*		linked_list.h
*
* DESCRIPTION :
* 		Linked list api functions prototypes
*		and required data structures (e.g. list Node)
*
* AUTHOR:
* 		WesternSage - 04 Agus 2019
*
***********************************************************************/

#ifndef LINKED_LIST
#define LINKED_LIST

struct Node {
	int data;
	struct Node *next;
} typedef Node;

// TODO: Implement append func

Node *list_new();                                   // create empty list
void list_print(Node *head_ptr);                    // print list
void list_rprint(Node *head_ptr);                   // recursive print
void list_rrprint(Node *head_ptr);                  // recursive reverse print
void list_reverse(Node **head_ptr);                 // revese list
void list_remove(int n, Node **head_ptr);           // remove item at pos n
void list_rreverse(Node **head, Node *p);           // recursive reverse
void list_insert(int x, int n, Node **head_ptr);    // insert x at pos n

#endif
