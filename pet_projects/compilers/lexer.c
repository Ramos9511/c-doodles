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
    int head = getc(tape);

    if (isalpha(head)) {
        while (isalnum(head = getc(tape)));
        ungetc(head, tape);
        return ID;
    }

    ungetc(head, tape);
    return 0;
}

int isDEC(FILE * tape)
{
    int head = getc(tape);

    if (isdigit(head)) {
        if (head == '0') {
            ;
        } else {
            while (isdigit(head = getc(tape)));

			if (head == '.' && isdigit(head = getc(tape))) {
            	while (isdigit(head = getc(tape)));
            	ungetc(head, tape);
				return FLOAT;
			} 

			if (head == 'e') {
				if (isdigit(head = getc(tape))) {
            		while (isdigit(head = getc(tape)));
					ungetc(head, tape);
					return FLOAT;
				} else if (head == '+' || head == '-') {
					if (isdigit(head = getc(tape))) {
            			while (isdigit(head = getc(tape)));
						ungetc(head, tape);
						return FLOAT;
					}
				}
			}

            ungetc(head, tape);
			return INT;
        }
			
    } else {
		// this is crap
		if ((head == '-' || head == '.')) {
			if (isdigit(head = getc(tape))) {	
				while (isdigit(head = getc(tape)));
				if (head == 'e') {
					if (isdigit(head = getc(tape))) {
						while (isdigit(head = getc(tape)));
						ungetc(head, tape);
						return FLOAT;
					}
					ungetc(head, tape);
					return FLOAT;	
				}
				ungetc(head, tape);
			}
			ungetc(head, tape);

			return FLOAT;
		}
	}

    ungetc(head, tape);
    return 0;
}

int isASGN(FILE *tape)
{
	int head = getc(tape);

	if (head == ':') {
		if ( (head = getc(tape)) == '=' ) {
			return ASGN;
		}
	}
	ungetc(head, tape);
	return 0;
}
