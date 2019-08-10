/***********************************************************************
*
* FILENAME:
*	stack_array.c
*
* DESCRIPTION :
* 	Implementation of stack api functions using arrays
*
* AUTHOR:
* 	WesternSage - 06 Augus 2019
*
***********************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 50
#define STACK_BASE -1

struct stack {
	int s[MAX_SIZE];
	int top;
} typedef Stack;

Stack * stack_new();
int stack_top(Stack *head);
void stack_pop(Stack *head);
void stack_push(int x, Stack *head);

Stack * stack_new()
{
	Stack *new_stack = (Stack*)malloc(sizeof(Stack));
	new_stack->top = STACK_BASE;
	return new_stack;
}

int stack_top(Stack *head)
{
	return head->s[head->top];
}

void stack_push(int x, Stack *head)
{
	if (head->top == MAX_SIZE - 1)
		printf("%s\n","Stack overflow!");
	else
		head->s[++(head->top)] = x;
}

void stack_pop(Stack *head)
{
	if (head->top == STACK_BASE)
		printf("%s\n", "Stack underflow!");
	else
		head->top--;
}

/* test cases */
int main(int argc, char * argv[])
{
	Stack *head = stack_new();
	stack_push(1, head);
	stack_push(2, head);
	stack_push(3, head);
	printf("%d\n",stack_top(head));
	stack_pop(head);
	printf("%d\n",stack_top(head));
	stack_pop(head);
	printf("%d\n",stack_top(head));
	stack_pop(head);
	return 0;
}
