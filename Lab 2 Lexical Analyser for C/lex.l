%option noyywrap
%{
#include <stdio.h>
%}

/* Regular expressions to match tokens */
%%
"auto"      { printf("AUTO keyword\n"); }
"break"     { printf("BREAK keyword\n"); }
"case"      { printf("CASE keyword\n"); }
"char"      { printf("CHAR keyword\n"); }
"const"     { printf("CONST keyword\n"); }
"continue"  { printf("CONTINUE keyword\n"); }
"int"       { printf("INT keyword\n"); }
"return"    { printf("RETURN keyword\n"); }

[a-zA-Z_][a-zA-Z0-9_]*   { printf("IDENTIFIER: %s\n", yytext); }
[0-9]+                   { printf("NUMBER: %s\n", yytext); }
"+"                      { printf("PLUS\n"); }
"-"                      { printf("MINUS\n"); }
"="                      { printf("ASSIGN\n"); }
"("                      { printf("LPAREN\n"); }
")"                      { printf("RPAREN\n"); }
"{"                      { printf("LBRACE\n"); }
"}"                      { printf("RBRACE\n"); }
";"                      { printf("SEMICOLON\n"); }
","                      { printf("COMMA\n"); }
"->"                     { printf("ARROW\n"); } // Optional: for pointers
"*"                      { printf("STAR\n"); } // Optional: for multiplication
"/"                      { printf("SLASH\n"); } // Optional: for division
"%"                      { printf("PERCENT\n"); } // Optional: for modulus

[ \t\n]+    ; /* Ignore whitespace */
.           { printf("UNKNOWN TOKEN: %s\n", yytext); }
%%

int main(void)
{
    yylex();  // Call the generated lexer function
    return 0;
}
