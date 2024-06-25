%option noyywrap nodefault yylineno

%{
#include <stdio.h>
#include "src/ast.h"
#include "another.tab.h"
%}

%%

\+     {yylval.text = strdup(yytext); return PLUS;}
\-     {yylval.text = strdup(yytext); return MINUS;}
\*     {yylval.text = strdup(yytext); return MUL;}
\/     {yylval.text = strdup(yytext); return DIVIDE;}
\=     {return ASSIGN;}
\;     {return SEPARATOR;}
\(     {return L_SKOBKA;}
\)     {return R_SKOBKA;}
\>     {yylval.text = strdup(yytext); return GT;}
\<     {yylval.text = strdup(yytext); return LESS;}
\>\=    {yylval.text = strdup(yytext); return GT_EQ;}
\<\=    {yylval.text = strdup(yytext); return LESS_EQ;}
\=\=    {yylval.text = strdup(yytext); return EQUALS;}
\!\=    {yylval.text = strdup(yytext); return NOT_EQUALS;}
\&\&    {yylval.text = strdup(yytext); return AND;}
\|\|    {yylval.text = strdup(yytext); return OR;}
\\    {return LAMBDA;}
->    {return ARROW;}
let   {return LET;}
in    {return IN;}
case  {return CASE;}
%     {yylval.text = strdup(yytext);return MOD;}
[A-Za-z_][A-Za-z0-9_]* {yylval.text = strdup(yytext); return NAME;}
[+-]?[0-9]+  {yylval.num = atoi(yytext); return DIGIT;}
[ \t\r\n]     { }
.	{ yyerror("Mystery character \"%c\"\n"); }

%%