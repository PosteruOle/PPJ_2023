parser: parser.o lexer.o
	g++ parser.o lexer.o -o parser

parser.o: parser.cpp tokeni.hpp
	g++ -c parser.cpp -o parser.o

lexer.o: lex.yy.c tokeni.hpp
	g++ -c lex.yy.c -o lexer.o	

lex.yy.c: lexer.lex tokeni.hpp
	flex lexer.lex

.PHONY: clean

clean:
	rm -rf parser *.o *.yy.*