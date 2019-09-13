/*
 * @<parser.c>::
 */

#include <stdio.h>
#include <stdlib.h>
#include <main.h>
#include <tokens.h>
#include <parser.h>
#include <lex_par_interface.h>

/*
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

/*
 * grammar emulation functions 
 */
void
expr(void)
{
    term();
    rest();
}

void
rest(void)
{
    switch (lookahead) {
    case '+':
    case '-':
        match(lookahead);
        term();
        rest();
        break;
    default:
        ;
    }
}

void
term(void)
{
    fact();
    quoc();
}

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
    default:
        ;
    }
}

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
    case DEC:
        match(DEC);
        break;
    default:
        match('(');
        expr();
        match(')');
    }
}
