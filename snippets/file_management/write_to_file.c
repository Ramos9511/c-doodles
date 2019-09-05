/**
*	FILE: write_to_file.c 
*
*	DESCRIPTION: Write an input string 
*	of unknown size to a text file (Esc 
*	key to quit)
*
*	AUTHOR: gfvante - 11 August 2019
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
#define ESCAPE_ASCII_CODE 27

int main(int argc, char * argv[])
{
  FILE *f;
  if (!(f = fopen("file.txt", "w"))) {
    printf("%s\n", "Error opening file!\n");
    exit(1);
  };

  int i = 0;

  // allocate a byte for first char
  char *text = malloc(1), ch;

  printf("%s\n", "Type something: ");

  /* iterate over all chars of string
	 loading each one to memory */
  while ((ch = getchar()) != ESCAPE_ASCII_CODE) {
    text[i++] = ch;
	/* 1 more byte for each 
	   character read */
    text = realloc(text, i+1);
    if (!text) exit(1);
  }

  text[i] = '\0';

  // write final string to file
  fprintf(f, "%s\n", text);
  fclose(f);
}
