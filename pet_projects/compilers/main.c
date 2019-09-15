/*
 * @<main.c>::
 */

/** system include libraries **/
#include <stdio.h>
#include <ctype.h>

/** NOTE: compile with -I. directive flag **/
#include <main.h>
#include <parser.h>
#include <lex_par_interface.h>

// defining extern variables
int lookahead;
FILE *source, *object;

int main(int argc, char *argv[])
{
    source = stdin;
    object = stdout;

	// testing parser

	//fputs("Testing lexer:\n", stdout);

	lookahead = gettoken(source);
	
	//char rejected = getc(source);
	//fprintf(stdout, "First rejected token was %x\n", rejected);

	// testing parser
	//fputs("Testing parser:\n", stdout);

	expr();

}




