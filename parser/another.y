
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

program: supercombinators

supercombinators: supercombinator SEPARATOR supercombinators
    | supercombinator SEPARATOR

supercombinator: vars ASSIGN expression

vars: var vars
    | var

var: NAME

expression: LET defuns IN expression
    | CASE expression IN alts
    | LAMBDA vars ARROW expression
    | expr1

expr1: expr2 OR expr1
    | expr2

expr2: expr3 AND expr2
    | expr3

expr3: expr4 relop expr4
    | expr4

expr4: expr5 PLUS expr4
    | expr5 MINUS expr5
    | expr5

expr5: expr6 MUL expr5
    | expr6 DIVIDE expr6
    | expr6 MOD expr6
    | expr6

expr6: aexprs

defuns: defun SEPARATOR defuns
    | defun SEPARATOR

defun: var ASSIGN expression

alts: alt SEPARATOR alts
    | alt

alt: DIGIT vars ARROW expression

relop: LESS | LESS_EQ | GT | GT_EQ | EQUALS | NOT_EQUALS

aexprs: aexpr aexprs
    | aexpr

aexpr: var
    | DIGIT
    | L_SKOBKA expression R_SKOBKA

%%