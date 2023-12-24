parser: parser.o lexer.o polinomi.o
	g++ parser.o lexer.o polinomi.o -o parser
	
parser.o: parser.tab.cpp parser.tab.hpp polinomi.o
	g++ -c parser.tab.cpp -o parser.o 

lexer.o: lex.yy.c parser.tab.hpp polinomi.o
	g++ -c lex.yy.c -o lexer.o

lex.yy.c: lexer.lex
	flex lexer.lex

parser.tab.cpp parser.tab.hpp: parser.ypp
	bison -d -v parser.ypp

polinomi.o: polinomi.cpp polinomi.hpp		
	g++ -c polinomi.cpp -o polinomi.o

.PHONY: clean

clean:
	rm *.o *.output *.tab.* *.yy.* parser