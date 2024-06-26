#include <stdio.h>
#include "src/ast.h"
#include "another.tab.h"
#include "util/state_machine.h"

extern int yyparse(program_t*);

void yyerror (char const *s) {
   fprintf (stderr, "%s\n", s);
 }

int main(void)
{
    program_t* program = malloc(sizeof(program_t));
    if(yyparse(program)) printProgram(program);

    eval(compile(program));
}
