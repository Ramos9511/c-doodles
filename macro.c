#include <stdio.h>
#include <stdlib.h>

#define START int main(int argc, char * argv[])
#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define PRINT(str, type) printf(#type "\n", str)
#define FOR(S) for (int i = 1; i < S; i++)
#define BEGIN {
#define END }

START

BEGIN
	FOR(argc)
		PRINT(argv[i], %s);
	
	PRINT(MAX(20, MAX(10, 12)), %d);
	
	return EXIT_SUCCESS;
END