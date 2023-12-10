parser: parser.o lexer.o funkcije.o
	g++ parser.o lexer.o funkcije.o -o parser

parser.o: parser.tab.cpp parser.tab.hpp funkcije.hpp
	g++ -c parser.tab.cpp -o parser.o

lexer.o: lex.yy.c parser.tab.hpp funkcije.hpp
	g++ -c lex.yy.c -o lexer.o

lex.yy.c: lexer.lex parser.tab.hpp funkcije.hpp
	flex lexer.lex

parser.tab.cpp parser.tab.hpp: parser.ypp funkcije.hpp
	bison -d -v parser.ypp

funkcije.o: funkcije.cpp funkcije.hpp
	g++ -c funkcije.cpp -o funkcije.o

.PHONY: clean

clean:
	rm -rf parser *.o *.yy.* *.tab.* *.output