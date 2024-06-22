PARSER=another


lex: lexer/lexer.l
	flex lexer/lexer.l

parser: parser/${PARSER}.y
	bison -d -Wcounterexamples parser/${PARSER}.y

compile: main.c src/ast.c parser lexer
	gcc lex.yy.c another.tab.c main.c -o calpi

run:
	./calpi

clean:
	rm *.tab.*
	rm *.yy.c