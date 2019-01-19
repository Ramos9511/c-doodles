#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

# define MAXLEN 10

char * myStrcat(char * s1, const char * s2);

int main()
{
	char s1[MAXLEN + 1] = "abcd";
	char * s2 = "efg";
	
	myStrcat(s1, s2);
	
	printf("s1 + s2 is %s \n", s1);
	
	return EXIT_SUCCESS;
}

char * myStrcat(char * s1, const char * s2) 
{
	while(*s1)
		s1++;
	
	while(*s1++ = *s2++)
		;
	
	return s1;
		
}

