/***********************************************************************
*
* FILENAME:
*	  write_to_file.c
*
* DESCRIPTION :
* 	Write an input string of unknown
*   size to a text file (Esc key to quit)
*
* AUTHOR:
* 	WesternSage - 11 August 2019
*
***********************************************************************/

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
  char *text = malloc(1), ch;

  printf("%s\n", "Type something: ");

  while ((ch = getchar()) != ESCAPE_ASCII_CODE) {
    text[i++] = ch;
    text = realloc(text, i+1);
    if (!text) exit(1);
  }
  text[i] = '\0';
  fprintf(f, "%s\n", text);
  fclose(f);

  return 0;
}
