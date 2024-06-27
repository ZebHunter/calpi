PARSER=another


lex: lexer/lexer.l
	flex lexer/lexer.l

parser: parser/${PARSER}.y
	bison -d parser/${PARSER}.y

compile:  parser lex
	gcc lex.yy.c another.tab.c src/ast.c main.c util/heap.c util/map.c util/state_machine.c -o calpi

run:
	./calpi

clean:
	rm *.tab.*
	rm *.yy.c
	rm jopa

.PHONY: parser lex clean
