lexer: lex.yy.c
	gcc lex.yy.c -o lexer

lex.yy.c: ccomments.lex
	flex ccomments.lex

.PHONY: clean

clean:
	rm lexer lex.yy.c	
