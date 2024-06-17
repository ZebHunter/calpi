
lexer: lexer/lexer.l
	flex lexer/lexer.l

parser: parser/parser.y
	bison -d -Wconflicts-sr -Wconflicts-rr parser/parser.y

compile: main.c src/ast.c parser lexer
	gcc lex.yy.c parser.tab.c main.c -o calpi

run:
	./calpi
