
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
%token LAMBDA NOT

%left PLUS MINUS
%left MUL 
%right ASSIGN


%start program


%%

program: functions                                  {printf("program: functions\n");}

functions: function SEPARATOR functions             {printf("functions: function; function\n");}
    | function                                      {printf("functions: function; functions\n");}

function: statement definition ASSIGN expression    {printf("function: statement\n definition -> expression\n");}   //Если что, оставить это
    | definition ASSIGN expression                  {printf("function: definition -> expression\n");}

statement: func_name TYPE_SEP types                 {printf("statement: f_name :: list types\n");}

types: types ARROW types                            {printf("list_types: type -> type\n");}
    | L_SKOBKA types R_SKOBKA                       {printf("list_types: type -> list_types\n");}
    | type                                          {printf("list_types: type\n");}

type: INT | BOOL                                    {printf("type: Int | Bool\n");}

definition: func_name list_args                     {printf("deinition: f_name list_args\n");}
    | func_name L_SKOBKA list_args R_SKOBKA         {printf("definition: f_name(list_args)\n");}

list_args: arg COMMA list_args                      {printf("list_args: arg, list_args\n");}
    | arg list_args                                 {printf("list_args: arg list_args\n");}
    | arg                                           {printf("list_args: arg\n");}

arg: NAME                                           {printf("arg: Name\n");}

func_name: NAME                                     {printf("f_name: Name\n");}

calling: func_name expressions

expressions: expression expressions
    | expression
    |

expression: condition                               {printf("expression: condition");}
    | math_exp                                      {printf("expression: math_exp");}
    | logic_exp                                     {printf("expression: logic_exp");}
    | function                                      {printf("expression: function");}
    | expression WHERE functions                    {printf("expression: condition");}
    | definition                                    {printf("expression: definition");}
    | digit                                         {printf("expression: digit");}

condition: IF expression THEN expression ELSE expression           {printf("condition: jopa");}
    | IF expression THEN expression list_elif ELSE expression      {printf("condition: jopa");}

list_elif: ELIF expression THEN expression                         {printf("condition: jopa");}
    | ELIF expression THEN expression list_elif                    {printf("condition: jopa");}

math_exp: expression PLUS term                                     {printf("math: jopa");}
    | expression MINUS term                                        {printf("math: jopa");}
    | term                                                         {printf("math: jopa");}

term: term MUL factor                                              {printf("math: jopa");}
    | term DIVIDE factor                                           {printf("math: jopa");}
    | factor                                                       {printf("math: jopa");}

factor: digit
    | L_SKOBKA math_exp R_SKOBKA                                   {printf("math: jopa");}

digit: DIGIT                                                       {printf("math: jopa");}

logic_exp: expression AND expression                               {printf("logic: jopa");}
    | expression OR expression                                     {printf("logic: jopa");}
    | expression LESS expression                                   {printf("logic: jopa");}
    | expression LESS_EQ expression                                {printf("logic: jopa");}
    | expression GT expression                                     {printf("logic: jopa");}
    | expression GT_EQ expression                                  {printf("logic: jopa");}
    | expression EQUALS expression                                 {printf("logic: jopa");}
    | expression NOT_EQUALS expression                             {printf("logic: jopa");}


%%