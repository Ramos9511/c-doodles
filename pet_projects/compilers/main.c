/*
 * @<main.c>::
 */

/** system include libraries **/
#include <stdio.h>

/** NOTE: compile with -I. directive flag **/
#include <main.h>
#include <parser.h>
#include <ctype.h>
#include <lex_par_interface.h>

// defining extern variables
int lookahead;
FILE *source, *object;

int main(int argc, char *argv[])
{
    source = stdin;
    object = stdout;

	fputs("Testing lexer:\n", stdout);

	lookahead = gettoken(source);
	fprintf(stdout, "Token: %d\n", lookahead);

	char rejected = getc(source);
	if (isalnum(rejected))
		fprintf(stdout, "The token %c was rejected", rejected);

}




