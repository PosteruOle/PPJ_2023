parser: parser.o lexer.o table.o tree.o
	g++ parser.o lexer.o table.o tree.o -o parser
parser.o: parser.tab.cpp parser.tab.hpp
	g++ -c parser.tab.cpp -o parser.o
lexer.o: lex.yy.c
	g++ -c lex.yy.c -o lexer.o
lex.yy.c: lexer.l parser.tab.hpp
	flex -l lexer.l
parser.tab.cpp parser.tab.hpp: parser.ypp
	bison -d -v parser.ypp
tree.o: SyntaxTree.cpp SyntaxTree.hpp
	g++ -c SyntaxTree.cpp -o tree.o
table.o: SymbolTable.cpp SymbolTable.hpp
	g++ -c SymbolTable.cpp -o table.o


.PHONY: clean

clean:
	rm -rd *.yy.* *.tab.* *.o *.output parser