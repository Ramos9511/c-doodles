/***********************************************************************
*
* FILENAME:
*	  dump_file_content.c
*
* DESCRIPTION :
* 	Dumps content of a given file on stdout
*   in hexadecimal format
*
* AUTHOR:
* 	WesternSage - 11 August 2019
*
***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define BYTES_PER_LINE 16

int main(int argc, char * argv[])
{
  FILE *f;
  if (!(f = fopen("dump_file.txt", "r"))) {
    printf("%s\n", "Problem opening file!");
    exit(1);
  }

  int bytes_read;
  char chunk[BYTES_PER_LINE]; // +1 for null terminator character

  while ((bytes_read = fread(chunk, 1, sizeof(chunk), f)) > 0) {
    for (int i = 0; i < bytes_read; i++)
      printf("0x%02x ", chunk[i]);
    printf("%s","\t" );
    for (int i = 0; i < bytes_read; i++)
      if (isprint(chunk[i]))
        printf("%c ", chunk[i]);
      else
        printf("%c ", '.');
    printf("\n");
  }

  fclose(f);
  return 0;
}
