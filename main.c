#include <stdio.h>
//#include "src/ast.h"
#include "another.tab.h"

void yyerror (char const *s) {
   fprintf (stderr, "%s\n", s);
 }

int main(void)
{
    return yyparse();
}
