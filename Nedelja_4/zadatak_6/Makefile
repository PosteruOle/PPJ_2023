lexer: lex.yy.c
	gcc -Wall lex.yy.c -o lexer

lex.yy.c: rimski.lex
	flex rimski.lex

.PHONY: clean

clean:
	rm lexer lex.yy.c	
