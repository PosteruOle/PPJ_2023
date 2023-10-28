lexer: lex.yy.c
	gcc -Wall lex.yy.c -o lexer

lex.yy.c: const.lex
	flex const.lex

.PHONY: clean

clean:
	rm lexer lex.yy.c	
