/**
*	FILE: dump_file_content.c
*
*	DESCRIPTION: Dumps content of a 
*	given file on stdout in hexadecimal 
*   format
*
*	AUTHOR: gfvante - 11 August 2019
* 
*   NOTE ====================================== 
*   Error handling has not been implemented 
*   for clarity purposes. If you plan on using 
*   this code as part of a real application you 
*   you should implement it! 
*   ===========================================
*/

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

  // line-size buffer
  char chunk[BYTES_PER_LINE]; 

  // reads in chunks of 16 bytes
  while ((bytes_read = fread(chunk, 1, sizeof(chunk), f)) > 0) {

	// print hex value of each char in chunk
    for (int i = 0; i < bytes_read; i++)
      printf("0x%02X ", chunk[i]);

	printf("%s","\t" );
	
	// print ascii value of each char in chunk
    for (int i = 0; i < bytes_read; i++)
	  // print '.' if char isn't printable
      if (isprint(chunk[i]))
        printf("%c ", chunk[i]);
      else
        printf("%c ", '.');

    printf("\n");
  }

  fclose(f);
}
