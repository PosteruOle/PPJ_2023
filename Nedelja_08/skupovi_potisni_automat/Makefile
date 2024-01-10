parser: parser.o lexer.o
	g++ parser.o lexer.o -o parser

lexer.o: lex.yy.c tokeni.hpp
	g++ -c lex.yy.c -o lexer.o

lex.yy.c: lexer.lex tokeni.hpp
	flex lexer.lex

parser.o: parser.cpp tokeni.hpp
	g++ -c parser.cpp -o parser.o

.PHONY: clean

clean:
	rm parser *.o *.yy.*