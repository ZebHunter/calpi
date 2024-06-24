
%{
#include <stdio.h>
#include <stdint.h>
//#include "../src/ast.h"
%}


%union {
    char* text;
    int num;
}

%token IF THEN ELSE ELIF
%token SEPARATOR
%token ASSIGN
%token TYPE_SEP
%token ARROW
%token INT BOOL
%token COMMA
%token L_SKOBKA R_SKOBKA
%token WHERE
%token PLUS MINUS MUL DIVIDE
%token AND OR LESS LESS_EQ GT GT_EQ EQUALS NOT_EQUALS
%token<text> NAME
%token<num> DIGIT
%token LAMBDA LET IN CASE MOD

%left PLUS MINUS
%left MUL 
%right ASSIGN


%start program


%%

//program_t*
program: supercombinators

//program_t*
supercombinators: supercombinator SEPARATOR supercombinators
    | supercombinator SEPARATOR

//supercomp_t*
supercombinator: vars ASSIGN expression

//string_list_t*
vars: var vars
    | var

//char*
var: NAME

//expr_t*
expression: LET defuns IN expression
    //LETREC ???
    | CASE expression IN alts
    | LAMBDA vars ARROW expression
    | expr1

//expr_t*
expr1: expr2 OR expr1
    | expr2

//expr_t*
expr2: expr3 AND expr2
    | expr3

//expr_t*
expr3: expr4 relop expr4
    | expr4

//expr_t*
expr4: expr5 PLUS expr4
    | expr5 MINUS expr5
    | expr5

//expr_t*
expr5: expr6 MUL expr5
    | expr6 DIVIDE expr6
    | expr6 MOD expr6
    | expr6

//expr_t*
expr6: aexprs

//defs_list_t*
defuns: defun SEPARATOR defuns
    | defun SEPARATOR

//defs_list_t*
defun: vars ASSIGN expression

//alt_list*
alts: alt SEPARATOR alts
    | alt SEPARATOR

//alt_t*
alt: DIGIT vars ARROW expression

relop: LESS | LESS_EQ | GT | GT_EQ | EQUALS | NOT_EQUALS

//expr_t*
aexprs: aexpr aexprs
    | aexpr

//expr_t*
aexpr: var
    | DIGIT
    | L_SKOBKA expression R_SKOBKA

%%