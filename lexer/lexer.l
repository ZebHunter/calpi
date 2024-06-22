%option noyywrap nodefault yylineno

%{
#include <stdio.h>
//#include "../src/ast.h"
#include "another.tab.h"
%}

%%

"+"     {return PLUS;}
"-"     {return MINUS;}
"*"     {return MUL;}
"/"     {return DIVIDE;}
"="     {return ASSIGN;}
","     {return COMMA;}
";"     {return SEPARATOR;}
"("     {return L_SKOBKA;}
")"     {return R_SKOBKA;}
">"     {return GT;}
"<"     {return LESS;}
">="    {return GT_EQ;}
"<="    {return LESS_EQ;}
"=="    {return EQUALS;}
"!="    {return NOT_EQUALS;}
"&&"    {return AND;}
"||"    {return OR;}
"::"    {return TYPE_SEP;}
"if"    {return IF;}
"else"  {return ELSE;}
"then"  {return THEN;}
"\\"    {return LAMBDA;}
"Int"   {return INT;}
"Bool"  {return BOOL;}
"->"    {return ARROW;}
"where" {return WHERE;}
"let"   {return LET;}
"in"    {return IN;}
"case"  {return CASE;}
"%"     {return MOD;}
[a-z]+ {yylval.text = strdup(yytext); return NAME;}
[0-9]+ {yylval.num = atoi(yytext); return DIGIT;}
[ \t\r\n];
.	{ yyerror("Mystery character \"%c\"\n"); }

%%