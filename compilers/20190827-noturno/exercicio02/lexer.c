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
#include <stdlib.h>

/*
 * @ skipspaces:: 
 */

void
skipspaces(FILE * tape)
{
    int head;
    while (isspace(head = getc(tape)));
    ungetc(head, tape);
}

/*
 * @ isID:: 
 */
char lexeme[MAXIDLEN+1];
int
isID(FILE * tape)
{
    if (isalpha(lexeme[0] = getc(tape))) {
    	int i;
	for (i = 1; isalnum(lexeme[i] = getc(tape)); (i < MAXIDLEN) && i++);
        ungetc(lexeme[i], tape);
	lexeme[i] = 0;
        return ID;
    }

    ungetc(lexeme[0], tape);
    return 0;
}

// MARCELINO
// =============================================================================

/**********************************************************************
 * verify exponential
 * 0 if false
 * 1 if true
 * ********************************************************************/
int isEE(FILE *tape)
{
	int i = 0, *head = malloc(sizeof(int));

	if(toupper(head[i]=getc(tape)) == 'E')
	{
		i++;
		head = realloc(head,sizeof(int)*i);
		if((head[i]= getc(tape)) == '+' || head[i] == '-'){
			i++;
			head = realloc(head,sizeof(int)*i);
		} else {
			ungetc(head[i], tape);
		}

		if(isdigit(head[i] = getc(tape))){
			i++;
			head = realloc(head,sizeof(int)*i);
			while(isdigit(head[i] = getc(tape))){
				i++;
				head = realloc(head,sizeof(int)*i);
			}
			ungetc(head[i], tape);
			head[i] = 0;
			return 1;
		}
		for(; i > 0; i--) ungetc(head[i],tape);
	}
	ungetc(head[0], tape);
	free(head);
	return 0;
}

/***********************************************************************
 * REGEX:
 *		UINT = [1-9][0-9]*|0
 *		FRAC = UINT'.'[0-9]* | '.'[0-9]+
 *		EE   = [eE]['+''-']?[0-9]+
 *		FLT  = UINT EE | FRAC EE?
 ***********************************************************************/

int isNUM(FILE *tape)
{
	int head = getc(tape);
	int token = -1;
	if(isdigit(head)){
		token = UINT;
		if(head == '0')
		       	head = getc(tape);
		else
			while(isdigit(head = getc(tape)));
		
		if(head == '.'){
			token = FLT;
			while(isdigit(head = getc(tape)));
		}	

		ungetc(head, tape);
		if(isEE(tape))
			token = FLT;
		
		return token;
	}else if(head == '.') {
		if(isdigit(head = getc(tape)))
		{
			while(isdigit(head = getc(tape)));
			ungetc(head,tape);
			if(isEE(tape))
				return FLT;
			return token = FLT;
		}
		ungetc(head,tape);
		ungetc('.', tape);
		return 0;
	}

	ungetc(head,tape);
	return 0;

}

/* ======================================================================== */


/*
int
isDEC(FILE * tape)
{
    int             head = getc(tape);

    if (isdigit(head)) {
        if (head == '0') {
            ;
        } else {
            while (isdigit(head = getc(tape)));
            ungetc(head, tape);
        }
        return DEC;
    }
    ungetc(head, tape);
    return 0;
}
*/

int isASGN(FILE *tape)
{
	int head = getc(tape);

	if (head == ':') {
		if ( (head = getc(tape)) == '=' ) {
			return ASGN;
		}
		ungetc(head, tape);
		ungetc(':', tape);
		return 0;
	}
	ungetc(head, tape);
	return 0;
}


/*
 * lexer to parser interface: @ gettoken:: 
 */

int
gettoken(FILE * source)
{
    int             token;

    /*
     * ignore left spaces 
     */
    skipspaces(source);

    /*
     * lexical analysers are called hereafter: 
     */

    if (token = isID(source))
        return token;
    if (token = isDEC(source))
        return token;
    if (token = isASGN(source))
        return token;

    /*
     * return default token, say an ASCII value 
     */
    return getc(source);
}
