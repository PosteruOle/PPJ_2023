parser: parser.o lexer.o izrazi.o naredbe.o
	g++ parser.o lexer.o naredbe.o izrazi.o -o parser

parser.o: parser.tab.cpp parser.tab.hpp naredbe.hpp izrazi.hpp
	g++ -c parser.tab.cpp -o parser.o

lexer.o: lex.yy.c parser.tab.hpp naredbe.hpp izrazi.hpp
	g++ -c lex.yy.c -o lexer.o

lex.yy.c: lexer.lex parser.tab.hpp naredbe.hpp izrazi.hpp
	flex lexer.lex

parser.tab.cpp parser.tab.hpp: parser.ypp naredbe.hpp izrazi.hpp	
	bison -d -v parser.ypp

izrazi.o: izrazi.cpp izrazi.hpp	
	g++ -c izrazi.cpp -o izrazi.o

naredbe.o: naredbe.cpp naredbe.hpp
	g++ -c naredbe.cpp -o naredbe.o

.PHONY: clean

clean:
	rm -rf parser *.o *.yy.* *.tab.* *.output