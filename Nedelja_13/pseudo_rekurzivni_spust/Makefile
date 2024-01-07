parser: parser.o lexer.o
	gcc parser.o lexer.o -o parser
lexer.o: lex.yy.c tokeni.h
	gcc -c lex.yy.c -o lexer.o
parser.o: parser.c tokeni.h
	gcc -c parser.c -o parser.o
lex.yy.c: lexer.l tokeni.h
	flex lexer.l

.PHONY: clean

clean:
	rm parser *.o *.yy.* *.tab.*
