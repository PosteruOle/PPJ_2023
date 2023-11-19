parser: parser.o lexer.o
	g++ -std=c++14 parser.o lexer.o -o parser 

parser.o: parser.tab.cpp parser.tab.hpp
	g++ -std=c++14 -c parser.tab.cpp -o parser.o

lexer.o: lex.yy.c parser.tab.hpp
	g++ -std=c++14 -c lex.yy.c -o lexer.o

lex.yy.c: lexer.lex parser.tab.hpp
	flex lexer.lex

parser.tab.cpp parser.tab.hpp: parser.ypp
	bison -dv parser.ypp

.PHONY: clean

clean: 
	rm	-rf *.o *.tab.* *.yy.* parser *.output