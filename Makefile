PARSER=another


lex: lexer/lexer.l
	flex lexer/lexer.l

parser: parser/${PARSER}.y
	bison -d parser/${PARSER}.y

compile: main.c src/ast.c parser lexer
	gcc lex.yy.c another.tab.c util/node.h src/ast.h src/ast.c main.c -o calpi

run:
	./calpi

clean:
	rm *.tab.*
	rm *.yy.c
	rm jopa

try: parser lex
	gcc lex.yy.c another.tab.c src/ast.c main.c util/heap.c util/map.c util/state_machine.c -o jopa

.PHONY: parser lex clean