%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>  // Add this line
void yyerror(const char *s);
int yylex();
#include "parser.tab.h"  // Bison-generated header with token definitions
%}

%%

"int"           { return INT; }
"float"         { return FLOAT; }
"if"            { return IF; }
"else"          { return ELSE; }
"while"         { return WHILE; }
"return"        { return RETURN; }
"+"             { return PLUS; }
"-"             { return MINUS; }
"*"             { return MUL; }
"/"             { return DIV; }
"="             { return ASSIGN; }
";"             { return SEMI; }
"("             { return LPAREN; }
")"             { return RPAREN; }
"{"             { return LBRACE; }
"}"             { return RBRACE; }

[0-9]+          { yylval.ival = atoi(yytext); return NUMBER; }
[a-zA-Z_][a-zA-Z0-9_]*  { yylval.sval = strdup(yytext); return ID; }

[ \t\n]+        { /* Ignore whitespaces */ }

.               { printf("Unexpected character: %s\n", yytext); }

%%

int yywrap() { return 1; }
