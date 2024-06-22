
lexer: lexer/lexer.l
	flex lexer/lexer.l

parser: parser/parser.y
	bison -d parser/parser.y

another: parser/another.y
	bison -d parser/another.y

compile: main.c src/ast.c another lexer
	gcc lex.yy.c another.tab.c main.c -o calpi

run:
	./calpi
