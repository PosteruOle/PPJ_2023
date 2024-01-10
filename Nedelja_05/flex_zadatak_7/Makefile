lexer: lex.yy.c
	gcc lex.yy.c -o lexer
	
lex.yy.c: scanner.lex
	flex scanner.lex

.PHONY: clean

clean:
	rm -rf lexer lex.yy.c	
