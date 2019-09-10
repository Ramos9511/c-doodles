/*
 * @<main.c>::
 */

/** system include libraries **/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


#define UINT 1024
#define FLOAT 1025


FILE           *source,
               *object;

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
		}else {
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
			token = FLOAT;
			while(isdigit(head = getc(tape)));
		}	

		ungetc(head, tape);
		if(isEE(tape))
			token = FLOAT;
		
		return token;
	}else if(head == '.') {
		if(isdigit(head = getc(tape)))
		{
			while(isdigit(head = getc(tape)));
			ungetc(head,tape);
			if(isEE(tape))
				return FLOAT;
			return token = FLOAT;
		}
		ungetc(head,tape);
		ungetc('.', tape);
		return 0;
	}

	ungetc(head,tape);
	return 0;

}

int
main(int argc, char *argv[])
{
    source = stdin;
    object = stdout;

    int token = isNUM(source);

    printf("token: %d\n", token);

    return 0;

}
