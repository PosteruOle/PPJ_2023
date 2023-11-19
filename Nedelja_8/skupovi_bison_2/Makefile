parser: parser.o lexer.o skupovi.o
	g++ -std=c++14 parser.o lexer.o skupovi.o -o parser 

skupovi.o: skupovi.cpp skupovi.hpp
	g++ -c -std=c++11 skupovi.cpp -o skupovi.o

parser.o: parser.tab.cpp parser.tab.hpp skupovi.hpp
	g++ -std=c++14 -c parser.tab.cpp -o parser.o

lexer.o: lex.yy.c parser.tab.hpp skupovi.hpp
	g++ -std=c++14 -c lex.yy.c -o lexer.o

lex.yy.c: lexer.lex parser.tab.hpp skupovi.hpp
	flex lexer.lex

parser.tab.cpp parser.tab.hpp: parser.ypp skupovi.hpp
	bison -dv parser.ypp

.PHONY: clean

clean: 
	rm	-rf *.o *.tab.* *.yy.* parser *.output