/*
* @<parser.c>::
*
* 
* adopted grammar: LL(1) for simple expressions 
*
* expr -> term rest
* rest -> '+'term rest | '-'term rest | <empty>
* term -> fact quoc
* quoc -> '*'fact quoc | '/'fact quoc | <empty>
* fact -> ID [ := expr ] | DEC | '(' expr ')'
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <main.h>
#include <tokens.h>
#include <parser.h>
#include <lex_par_interface.h>

#define MAXIDLEN 32
char lexeme[MAXIDLEN+1];
int lokkahead;

/*
 * grammar emulation functions 
 */

int isOPLUS(void)
{
    switch (lookahead) {
        case '+':
	    return '+';
	case '-':
	    return '-';
	default:
	    return 0;
    }
}

int isOTIMES(void)
{
    switch (lookahead) {
        case '*':
	    return '*';
	case '/':
	    return '/';
	default:
	    return 0;
    }
}

void expr(void)
{
    int oplus;// = 0
    int otimes; // = 0
	
__term:
    //term();
__fact:  
    //fact();

    switch (lookahead) {
    case ID:

	    // print lexeme here
		print_lexeme();

        match(ID);
		if (lookahead == ASGN)
			match(ASGN); expr();
		break;
		
    case UINT:

	    // print lexeme here
		print_lexeme();

        match(UINT);
        break;

    case FLOAT:
		
	    // print lexeme here
		print_lexeme();

		match(FLOAT);
		break;

    default:
        match('(');
        expr();
        match(')');
    }

    /* abstracts { otimes fact } */
    if(otimes = isOTIMES()){
	    // print otimes here
        match(otimes);
            // otimes = 0
        goto __fact;
    }

    /* abstracts { oplus term } */
    if(oplus = isOPLUS()) {
	    // print oplus here
        match(oplus);
            // oplus = 0
        goto __term;
    }
}

// tmp utilitary

void print_lexeme()
{
 	// print lexeme here
	printf("Lexeme: ");
	for (int i = 0; i < MAXIDLEN; i++)
		printf("%c", lexeme[i]);
}
