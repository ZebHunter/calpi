
%{
#include <stdio.h>
#include <stdint.h>
#include "../src/ast.h"
%}

%parse-param {program_t* programs}

%union {
    char* text;
    int32_t num;
    expr_t* expr;
    program_t* program;
    supercomb_t* supercombinator;
    string_list_t* string_list;
    defs_list_t* defs_list;
    alt_list_t* alt_list;
    alt_t* alt;
}


%token SEPARATOR
%token ASSIGN
%token ARROW
%token L_SKOBKA R_SKOBKA
%token<text> PLUS MINUS MUL DIVIDE MOD
%token<text> AND OR LESS LESS_EQ GT GT_EQ EQUALS NOT_EQUALS
%token<text> NAME
%token<num> DIGIT
%token LAMBDA LET IN CASE

%left PLUS MINUS
%left MUL DIVIDE
%right ASSIGN

%type<program> program
%type<program> supercombinators
%type<supercombinator> supercombinator
%type<text> var
%type<string_list> vars
%type<expr> expression
%type<expr> expr1
%type<expr> expr2
%type<expr> expr3
%type<expr> expr4
%type<expr> expr5
%type<expr> expr6
%type<defs_list> defuns
%type<defs_list> defun
%type<alt_list> alts
%type<alt> alt
%type<expr> aexprs
%type<expr> aexpr
%type<text> relop

%start program


%%

//program_t*
program: supercombinators       {programs = $1;}

//program_t*
supercombinators: supercombinator SEPARATOR supercombinators        {$$ = addProgramNode($1, $3);}
    | supercombinator SEPARATOR             {$$ = addProgramNode($1, NULL);}

//supercomb_t*
supercombinator: vars ASSIGN expression    {$$ = addSupercomb($1, $3);} 

//string_list_t*
vars: var vars                              {$$ = addArgsList($1, $2);}
    | var                                   {$$ = addArgsList($1, NULL);}

//char*
var: NAME                                   {$$ = $1}

//expr_t*
expression: LET defuns IN expression        {$$ = addLetExpr($2, $4);}
    //LETREC ???
    | CASE expression IN alts               {$$ = addCaseExpr($2, $4);}
    | LAMBDA vars ARROW expression          {$$ = addLambda($2, $4);}
    | expr1                                 {$$ = wrapperExprOperation(NULL, $1);}

//expr_t*
expr1: expr2 OR expr1           {$$ = wrapperExprOperation(addExprOperation($2, $1), $3);}
    | expr2                     {$$ = wrapperExprOperation(NULL, $1);}

//expr_t*
expr2: expr3 AND expr2          {$$ = wrapperExprOperation(addExprOperation($2, $1), $3);}
    | expr3                     {$$ = wrapperExprOperation(NULL, $1);}

//expr_t*
expr3: expr4 relop expr4        {$$ = wrapperExprOperation(addExprOperation($2, $1), $3);}
    | expr4                     {$$ = wrapperExprOperation(NULL, $1);}

//expr_t*
expr4: expr5 PLUS expr4         {$$ = wrapperExprOperation(addExprOperation($2, $1), $3);}
    | expr5 MINUS expr5         {$$ = wrapperExprOperation(addExprOperation($2, $1), $3);}
    | expr5                     {$$ = wrapperExprOperation(NULL, $1);}

//expr_t*
expr5: expr6 MUL expr5          {$$ = wrapperExprOperation(addExprOperation($2, $1), $3);}
    | expr6 DIVIDE expr6        {$$ = wrapperExprOperation(addExprOperation($2, $1), $3);}
    | expr6 MOD expr6           {$$ = wrapperExprOperation(addExprOperation($2, $1), $3);}
    | expr6                     {$$ = wrapperExprOperation(NULL, $1);}

//expr_t*
expr6: aexprs                   {$$ = wrapperExprOperation(NULL, $1);}

//defs_list_t*
defuns: defun SEPARATOR defuns    {$$ = addDefsList($1, $3);}
    | defun SEPARATOR             {$$ = addDefsList($1, NULL);}

//defs_list_t*
defun: var ASSIGN expression    {$$ = addDefun($1, $3);}

//alt_list_t*
alts: alt SEPARATOR alts    {$$ = addAltList($1, $3);}
    | alt SEPARATOR         {$$ = addAltList($1, NULL);}

//alt_t*
alt: DIGIT vars ARROW expression    {$$ = addAlt($1, $2, $4);}

relop: LESS | LESS_EQ | GT | GT_EQ | EQUALS | NOT_EQUALS

//expr_t*
aexprs: aexpr aexprs                    {$$ = wrapperExprOperation($1, $2);}
    | aexpr                             {$$ = wrapperExprOperation($1, NULL);}

//expr_t*
aexpr: var                              {$$ = addAexprVar($1);}
    | DIGIT                             {$$ = addAexprDigit($1);}
    | L_SKOBKA expression R_SKOBKA      {$$ = $2;}

%%