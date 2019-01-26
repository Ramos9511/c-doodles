#include <stdio.h>
#include <stdlib.h>

#define START int main(int argc, char * argv[])
#define PRINT(str, type) printf(#type "\n", str)
#define FOR(S) for (int i = 1; i < S; i++)

#define BEGIN {
#define END }

#define MAX(x, y) ((x) > (y) ? (x) : (y))

#define GENERIC_MAX(type)		\
type type##_max(type x, type y)	\
{								\
	return x > y ? x : y;		\
}

#define ECHO(s)		\
	do {			\
		gets(s);	\
		puts(s);	\
	} while (0)

#define ADD(x, y) (x + y)

#define TEST(condition, ...) ((condition) ? 	\
	printf("passed test: %s\n", #condition) : 	\
	printf(__VA_ARGS__))

GENERIC_MAX(int)

START

BEGIN
/* 	FOR(argc)
		PRINT(argv[i], %s);
	
	PRINT(MAX(20, MAX(10, 12)), %d);
	PRINT(int_max(20, 10), %d); */
	
/* 	PRINT("File name: " __FILE__, %s);
	PRINT("Today is: " __DATE__, %s);
	PRINT("Compilation time: " __TIME__, %s);
	PRINT(__STDC__, %d);
	PRINT(__STDC_HOSTED__, %d);
	PRINT(__STDC_VERSION__, %d); */
	
/* 	char s[10];
	ECHO(s); */
	
	TEST(3 > 10, "10 is greater than 3 \n");
	PRINT(__func__, %s);
	
	return EXIT_SUCCESS;
END