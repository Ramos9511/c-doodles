/***********************************************************************
*
* FILENAME: tail.c
*
* DESCRIPTION: implementation of unix 
* tail command using stack data structure
*
* AUTHOR: gfvante - 12 August 2019 
*
***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "type_definitions.h"
#include "stack_list.h"
#define LINE_SIZE 256

//TODO: Use a ring buffer of size number_of_lines
//TODO: Define ARRAY_SIZE(arr) macro

int main(int argc, char *argv[])
{
	/* getting args and checking for errs */

    if (argc < 2) {
        fprintf(stderr, "usage: %s LINES\n", argv[0]);
        return EXIT_FAILURE;
    }

    int number_of_lines = atoi(argv[1]);
    if (number_of_lines <= 0) {
        fputs("LINES must be a positive number\n", stderr);
        return EXIT_FAILURE;
    }

    FILE *f = fopen("file.txt", "r");
    if (!f) {
        perror("file.txt");
        return EXIT_FAILURE;
    };

    // push lines into stack
    Node *stack = stack_new();
    for (;;) {
        char *line = malloc(LINE_SIZE);
        if (!line) {
            fputs("Out of memory\n", stderr);
            return EXIT_FAILURE;
        }
        if (!fgets(line, LINE_SIZE, f)) {
            /* assume end of file */
            free(line);
            break;
        }
        stack_push(line, &stack);
    }

    // pop and print n lines to screen
    for (int i = 0; i < number_of_lines; i++) {
        char *line = stack_top(stack);
        fputs(line, stdout);
        free(line);
        stack_pop(&stack);
    }

    // free the remainder of the stack
    while (stack) {
        free(stack_top(stack));
        stack_pop(&stack);
    }
}
