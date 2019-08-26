/***********************************************************************
*
* FILENAME: parentheses_checker.c
*
* DESCRIPTION: Checks if a given expression
* has balanced block characters (e.g. '(', ')'
* '{','}', '[',']')
*
* AUTHOR: gfvante - 15 August 2019
*
***********************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../utils/type_definitions.h"
#include "../stack/stack_list/stack_list.h"

bool check_balance(char *str);

// test case
int main(int argc, char * argv[])
{
	char *str = "{[(a)]]}";
	if (check_balance(str)) {
		printf("%s\n", "Expression is balanced!");
	} else {
		printf("%s\n", "Expression is not balanced!");
	}

	return 0;
}

bool check_balance(char *str)
{
	Node *stack = stack_new();
	for (int i = 0; i < strlen(str); i++) {
		// push all openning chars
		if (str[i] == '(' || str[i] == '{' || str[i] == '[')
			stack_push(str[i], &stack);
		// check closing chars
		if (str[i] == ')' || str[i] == '}' || str[i] == ']') {
			if (stack_is_empty(stack))
				return false;
			// check for wrong pair match
			switch (str[i]) {
			case ')':
				if (stack_top(stack) != '(')
					return false;
				break;
			case '}':
				if (stack_top(stack) != '{')
					return false;
				break;
			case ']':
				if (stack_top(stack) != '[')
					return false;
				break;
			}
			// pop if pair is found
			stack_pop(&stack);
		}
	}
	return stack_is_empty(stack);
}
