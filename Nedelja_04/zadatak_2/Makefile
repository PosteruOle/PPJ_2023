lexer: lex.yy.c
	gcc lex.yy.c -o lexer

lex.yy.c: zagrade.lex
	flex zagrade.lex

.PHONY: clean

clean:
	rm lexer lex.yy.c	
