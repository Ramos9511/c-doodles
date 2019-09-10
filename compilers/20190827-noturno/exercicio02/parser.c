/*
 * @<parser.c>::
 */

#include <stdio.h>
#include <stdlib.h>

#include <parser.h>
#include <tokens.h>
#include <main.h>

/*
 * lexer-to-parser interface 
 */

int lookahead;
int  gettoken(FILE *);

/*
 * adopted grammar: LL(1) for simple expressions 
 */
/*************************************************
 * expr -> term rest
 * rest -> '+'term rest | '-'term rest | <empty>
 * term -> fact quoc
 * quoc -> '*'fact quoc | '/'fact quoc | <empty>
 * fact -> ID [ := expr ] | DEC | '(' expr ')'
 *************************************************/
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

void
expr(void)
{
    int oplus;
    int otimes;
__term:
    //term();
__fact:  
    //fact();
    switch (lookahead) {
    case ID:
        match(ID);
	if (lookahead == ASGN) {
		match(ASGN); expr();
	}
        break;
    case UINT:
        match(UINT);
        break;
    case FLT:
	match(FLT);
	break;
    default:
        match('(');
        expr();
        match(')');
    }
    /* abstracts { otimes fact } */
    if(otimes = isOTIMES()){
        match(otimes);
        goto __fact;
    }
    /* abstracts { oplus term } */
    if(oplus = isOPLUS()){
        match(oplus);
        goto __term;
    }
}

/* deprecated
void
term(void)
{
    int otimes;
__fact:  
    //fact();
    switch (lookahead) {
    case ID:
        match(ID);
	if (lookahead == ASGN) {
		match(ASGN); expr();
	}
        break;
    case UINT:
        match(UINT);
        break;
    case FLT:
	match(FLT);
	break;
    default:
        match('(');
        expr();
        match(')');
    }
    * abstracts { otimes fact }
    if(otimes = isOTIMES()){
        match(otimes);
        goto __fact;
    }

}
*/

void
quoc(void)
{
    switch (lookahead) {
    case '*':
    case '/':
        match(lookahead);
        fact();
        quoc();
        break;
     case-1:case')':
     case'+':case'-':
		break;
     default:
        fprintf(stderr,
	"ilegal trailing symbol: '%c'\n", lookahead);
	exit(-3);
    }
}

/* deprecated 
void 
fact(void)
{
    switch (lookahead) {
    case ID:
        match(ID);
	if (lookahead == ASGN) {
		match(ASGN); expr();
	}
        break;
    case UINT:
        match(UINT);
        break;
    case FLT:
	match(FLT);
	break;
    default:
        match('(');
        expr();
        match(')');
    }
}*/

/*
 * lexer-to-parser interface: 
 */
void
match(int expected)
{
    if (lookahead == expected) {
        lookahead = gettoken(source);
    } else {
        fprintf(stderr,
                "%d seen while %d was expected\n", lookahead, expected);
        exit(-2);
    }
}
