// lexer.h file

#pragma once

int isID(FILE *tape);
int isASGN(FILE *tape);
int isNUM(FILE *tape);
void match_EE(FILE *tape, int i_lex);
void skipspaces(FILE * tape);

