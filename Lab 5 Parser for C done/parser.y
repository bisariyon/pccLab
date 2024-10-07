%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void yyerror(const char *s);
int yylex();
%}

/* Define the types of values that tokens can return */
%union {
    int ival;      /* For integer values */
    float fval;    /* For floating-point values */
    char *sval;    /* For string values (identifiers and floating-point literals) */
}

/* Token declarations with their corresponding types */
%token <ival> NUMBER
%token <sval> ID
%token <sval> FLOAT
%token INT IF ELSE WHILE RETURN
%token PLUS MINUS MUL DIV ASSIGN SEMI
%token LPAREN RPAREN LBRACE RBRACE

%type <ival> expression term factor

%%

/* Start rule */
program:
    program declaration
    | declaration
    ;

declaration:
    type_specifier ID SEMI                               { printf("Declared variable: %s\n", $2); }
    | type_specifier ID ASSIGN expression SEMI           { printf("Assigned %s = %d\n", $2, $4); }
    | type_specifier ID ASSIGN FLOAT SEMI                { printf("Assigned %s = %s (float)\n", $2, $4); }
    | ID ASSIGN expression SEMI                          { printf("Assigned %s = %d\n", $1, $3); }
    ;

type_specifier:
    INT
    | FLOAT
    ;

expression:
    expression PLUS term    { $$ = $1 + $3; }
    | expression MINUS term { $$ = $1 - $3; }
    | term                  { $$ = $1; }
    ;

term:
    term MUL factor    { $$ = $1 * $3; }
    | term DIV factor  { $$ = $1 / $3; }
    | factor           { $$ = $1; }
    ;

factor:
    LPAREN expression RPAREN        { $$ = $2; }
    | ID                            { printf("Variable used: %s\n", $1); }
    | NUMBER                        { $$ = $1; }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main() {
    printf("Enter your C-like code:\n");
    return yyparse();
}
