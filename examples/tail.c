/***********************************************************************
*
* FILENAME:
*	  tail.c
*
* DESCRIPTION :
* 	implementation of unix tail command
*   using stack data structure
*
* AUTHOR:
* 	WesternSage - <date>
*
***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utils/type_definitions.h"
#include "../stack/stack_list/stack_list.h"
#define LINE_SIZE 256

int main(int argc, char *argv[])
{

  int number_of_lines;
  if (argc == 2) {
    number_of_lines = atoi(argv[1]);
  } else {
    printf("%s\n", "Error!");
    exit(1);
  }

  FILE *f;
  if (!(f = fopen("file.txt", "r"))) {
    printf("%s\n", "Error opening file!\n");
    exit(1);
  };

  // pushing lines into stack

  int i = 0;
  char *line, *temp = (char*)malloc(LINE_SIZE);
  Node *stack = stack_new();

  while (fgets(temp, sizeof(line), f) != NULL) {
    line = (char*)malloc(LINE_SIZE);
    strcpy(line, temp);
    stack_push((void*)line, &stack);
  }

  // poping and printing n lines to screen

  for (int i = 0; i < number_of_lines; i++) {
    printf("%s\n",(char*)stack_top(stack));
    stack_pop(&stack);
  }

  return 0;
}
