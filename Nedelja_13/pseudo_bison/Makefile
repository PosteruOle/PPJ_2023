parser: parser.o lexer.o broj.o
	g++ -std=c++11 parser.o broj.o lexer.o -o parser
broj.o: broj.cpp broj.hpp
	g++ -std=c++11 -c broj.cpp -o broj.o
lexer.o: lex.yy.c
	g++ -std=c++11 -c lex.yy.c -o lexer.o
parser.o: parser.tab.cpp parser.tab.hpp
	g++ -std=c++11 -c parser.tab.cpp -o parser.o
lex.yy.c: lexer.lex parser.tab.hpp
	flex lexer.lex
parser.tab.cpp parser.tab.hpp: parser.ypp
	bison -d -v parser.ypp

.PHONY: clean

clean:
	rm *.tab.* *.yy.* parser *.o *.output
