lexer: lex.yy.c
	gcc lex.yy.c -o lexer

lex.yy.c: pascal.lex
	flex pascal.lex

.PHONY: clean

clean:
	rm lexer lex.yy.c	
