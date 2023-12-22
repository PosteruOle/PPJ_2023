parser: parser.o lexer.o naredba.o izrazi.o
	g++ parser.o lexer.o naredba.o izrazi.o -o parser

parser.o: parser.tab.cpp parser.tab.hpp naredba.hpp izrazi.hpp
	g++ -c parser.tab.cpp -o parser.o

lexer.o: lex.yy.c parser.tab.hpp naredba.hpp izrazi.hpp
	g++ -c lex.yy.c -o lexer.o

lex.yy.c: lexer.lex parser.tab.hpp
	flex lexer.lex

parser.tab.cpp parser.tab.hpp: parser.ypp
	bison -d -v parser.ypp

naredba.o: naredba.cpp naredba.hpp
	g++ -c naredba.cpp -o naredba.o

izrazi.o: izrazi.cpp izrazi.hpp
	g++ -c izrazi.cpp -o izrazi.o

.PHONY: clean

clean:
	rm -rf parser *.tab.* *.yy.* *.o *.output