/**
*	FILE: binary_tree.c
*
*	DESCRIPTION: Implementation of binary
*	search tree api functions 
*
*	AUTHOR: gfvante - 20 August 2019
*
*   NOTE ======================================== 
*   Error handling has not been implemented 
*   for clarity purposes. If you plan on using 
*   this code as part of a real application you 
*   you should treat the possible error scenarios! 
*   ==============================================
*
*/

#include <stdio.h>
#include <stdlib.h>
#include "queue_list.h"

// binary_tree.h 
// ===============================

struct node {
	int data;
	struct node *left;
	struct node *right;
} typedef TNode;

TNode *new_tree();
int min(TNode *root);
int max(TNode *root);
int height(TNode *root);
TNode *new_node(int data);
int search(TNode *root, int data);
void insert(TNode **root, int data);

//===============================

int main(int argc, char *argv[])
{
	// test cases
	TNode *root = new_tree();
	insert(&root, 10);
	insert(&root, 5);
	insert(&root, 20);
	fprintf(stdout, "min: %d\n", min(root));
	fprintf(stdout, "max: %d\n", max(root));
	fprintf(stdout, "tree height: %d\n", height(root));
}

TNode *new_tree()
{
	return NULL;
}

TNode *new_node(int data)
{
	TNode *new_node = malloc(sizeof(TNode));
	new_node->data = data;
	new_node->left = NULL;
	new_node->right = NULL;
	return new_node;
}

// recursive insertion
void insert(TNode **root, int data)
{
	if (!(*root))
		*root = new_node(data);
	else if (data <= (*root)->data)
		insert(&(*root)->left, data);
	else
		insert(&(*root)->right, data);	
}

// recursive search
int search(TNode *root, int data) 
{
	if (!root) return 0;	// not found
	else if (root->data == data) return 1;
	else if (data <= root->data) search(root->left, data);
	else search(root->right, data);
}

int min(TNode *root)
{
	if (!root) exit(3); // error 
	if (!root->left)
		return root->data;
	min(root->left);
}

int max(TNode *root)
{
	if (!root) exit(3); // error 
	if (!root->right)
		return root->data;
	min(root->right);
}

int height(TNode *root)
{
	if (!root) // empty tree
		return -1;
	int left_height = height(root->left);
	int right_height = height(root->right);
	if (left_height > right_height)
		return left_height + 1;
	else
		return right_height + 1;
}


