#pragma once

int gettoken(FILE *);
void match(int expected);

#define MAXIDLEN 32
char lexeme[MAXIDLEN+1];
