lexer: lex.yy.c
	gcc lex.yy.c -o lexer

lex.yy.c: word_count.lex
	flex word_count.lex

.PHONY: clean

clean:
	rm lexer lex.yy.c	
