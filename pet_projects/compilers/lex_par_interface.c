/*****************************
 * lexer to parser interface:  
 ****************************/

#include <main.h>
#include <lexer.h>
#include <stdlib.h>

// Interface functions

/*
* gettoken
*/

int
gettoken(FILE * source)
{
    int token;

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
    return -10;
}

/*
 * mach tokens 
 */
void
match(int expected)
{
    if (lookahead == expected) {
        lookahead = gettoken(source);
    } else {
        fprintf(stderr,"%d seen while %d was expected\n", lookahead, expected);
        exit(-2);
    }
}
