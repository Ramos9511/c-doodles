#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

int myStrlen(const char * s);

int main()
{
	char * p = "abcde";
	
	printf("%s is %d characters long!\n",
		p, myStrlen(p));
	
	return EXIT_SUCCESS;
}

int myStrlen(const char * s) 
{
	size_t n = 0;
	
	while(*s++)
		n++;
	
	return n;
}