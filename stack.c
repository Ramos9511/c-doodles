
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define STACKSIZE 100

/* External variables */
int stack[STACKSIZE];
int top = 0;

void clearStack();
void push(int);
bool isEmpty();
bool isFull();
int pop();

int main(void)
{
	/* Testing out */


	if (isEmpty())
		printf("Stack is Empty!\n");

	for (int i = 0; i < STACKSIZE; i++)
		push(i);

	if (isFull())
		printf("Stack is full!\n");

	for (int i = 0; i < STACKSIZE; i++)
		printf("%d ", pop());

	clearStack();
	if (isEmpty())
		printf("\nClearStack() works!\n");

	return(EXIT_SUCCESS);
}

/* Stack functions */

void clearStack()
{
	top = 0;
}

bool isEmpty()
{
	return top == 0;
}

bool isFull()
{
	return top == STACKSIZE;
}

void push(int i)
{
	if (isFull())
		/* Stack overflow */
		exit(EXIT_FAILURE);
	else
		stack[top++] = i;
}

int pop()
{
	if (isEmpty()) {
		/* Stack underflow */
		exit(EXIT_FAILURE);
	} else {
		return stack[--top];
	}
}
