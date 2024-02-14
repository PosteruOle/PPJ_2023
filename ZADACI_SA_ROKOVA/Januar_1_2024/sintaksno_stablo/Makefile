parser: parser.o lexer.o naredba.o izrazi.o
	g++ parser.o lexer.o naredba.o izrazi.o -o parser

parser.o: parser.tab.cpp parser.tab.hpp
	g++ -c parser.tab.cpp -o parser.o

lexer.o: lex.yy.c parser.tab.hpp
	g++ -c lex.yy.c -o lexer.o

lex.yy.c: lexer.lex parser.tab.hpp
	flex lexer.lex

parser.tab.cpp parser.tab.hpp: parser.ypp naredba.hpp izrazi.hpp
	bison -d -v parser.ypp

izrazi.o: izrazi.cpp izrazi.hpp	
	g++ -c izrazi.cpp -o izrazi.o

naredba.o: naredba.cpp naredba.hpp
	g++ -c naredba.cpp -o naredba.o

.PHONY: clean

clean:
	rm -rf parser *.o *.yy.* *.output *.tab.*