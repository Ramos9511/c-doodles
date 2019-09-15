/*
 * @<lexer.c>::
 */

/*******************************************************
* Author: Eraldo Pereira Marinho, PhD
* Creation Date: Aug 13 19:20:59 -03 2019
********************************************************/

/*
 * Módulo para implementação de métodos de varredura léxica
 * *************************************************
 */

#include <stdio.h>
#include <ctype.h>
#include <tokens.h>
#include <lexer.h>
#include <lex_par_interface.h>

/*
 * @ skipspaces:: 
 */

void skipspaces(FILE * tape)
{
    int head;
    while (isspace(head = getc(tape)));
    ungetc(head, tape);
}

/*
 * @ isID:: 
 */

int isID(FILE * tape)
{
	int i;
	lexeme[0] = getc(tape);

    if (isalpha(lexeme[0])) {
		for (i = 1; isalnum(lexeme[i] = getc(tape)); (i < MAXIDLEN) && i++);
		ungetc(lexeme[i], tape);
		lexeme[i] = 0;
		return ID;
    }

    ungetc(lexeme[0], tape);
    return 0;
}

// this exists only to avoid clutter 
void match_EE(FILE *tape, int i_lex) {

	lexeme[i_lex] = getc(tape);

	// match EE
	if (lexeme[i_lex] == 'e') {

		// match '+' or '-'
		lexeme[++i_lex] = getc(tape);
		if (lexeme[i_lex] == '+' || lexeme[i_lex] == '-') {
			;
		} else {
			ungetc(lexeme[i_lex], tape);
			lexeme[i_lex] = 0;
		}

		lexeme[++i_lex] = getc(tape);
		
		// [0-9]+	
		if (isdigit(lexeme[i_lex])) {
			for (i_lex++; isdigit(lexeme[i_lex] = getc(tape)); i_lex < MAXIDLEN && i_lex++);
			ungetc(lexeme[i_lex], tape);
			lexeme[i_lex] = 0;
		} else {
			ungetc(lexeme[i_lex], tape);
			lexeme[i_lex] = 0;
		}

	} else {
		// not an 'e', put it back
		ungetc(lexeme[i_lex], tape);
		lexeme[i_lex] = 0;
	}
}


int isNUM(FILE *tape)
{
	int i;
	lexeme[0] = getc(tape);

	if (isdigit(lexeme[0])) {
		// 0 
		if (lexeme[0] == '0') return UINT;
	
		for (i = 1; isdigit(lexeme[i] = getc(tape)); i < MAXIDLEN && i++);

		// UINT'.'[0-9]*
		if (lexeme[i] == '.') {
			for (i++; isdigit(lexeme[i] = getc(tape)); i < MAXIDLEN && i++);
			ungetc(lexeme[i], tape);
			lexeme[i] = 0;

			// UINT'.'[0-9]* EE
			match_EE(tape, i);
			return FLOAT;
		}

		// UINT EE
		if (lexeme[i] == 'e') {
			ungetc(lexeme[i], tape);
			lexeme[i] = 0;
			match_EE(tape, i);
			return FLOAT;
		}

		// [1-9][0-9]*
		ungetc(lexeme[i], tape);
		lexeme[i] = 0;
		return UINT;

	// .[0-9]+EE
	} else if (lexeme[0] == '.') {

		lexeme[1] = getc(tape);
	
		//[0-9]+
		if (isdigit(lexeme[1])) {
		
			for (i = 2; isdigit(lexeme[i] = getc(tape)); i < MAXIDLEN && i++);

			if (lexeme[i]  == 'e') {
				ungetc(lexeme[i], tape);
				lexeme[i] = 0;
				match_EE(tape, i);
				return FLOAT;
			}

			ungetc(lexeme[i], tape);
			lexeme[i] = 0;
			return FLOAT;
		}

		// '.'(non-digit)
		ungetc(lexeme[1], tape);
		lexeme[1] = 0;
	}

	ungetc(lexeme[0], tape);
	lexeme[0] = 0;
    return 0;
}

int isASGN(FILE *tape)
{
	lexeme[0] = getc(tape);

	if (lexeme[0] == ':')
		if ((lexeme[1] = getc(tape)) == '=' )
			return ASGN;

	ungetc(lexeme[0], tape);
	lexeme[0] = 0;
	return 0;
}
