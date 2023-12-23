%option noyywrap

%{
    #include <iostream>
    #include <cstdlib>
    #include <map>
    #include "SymbolTable.hpp"
    #include "SyntaxTree.hpp"

    #include "parser.tab.hpp"
%}

%%

print   {return PRINT_T;}
def     {return DEF_T;}
[A-Za-z_][A-Za-z0-9_]*  {
                            yylval.s = new std::string(yytext);
                            return ID_T;
                        }
[0-9]+(\.[0-9]*)?   {
                        yylval.d = atof(yytext);
                        return BROJ_T;
                    }
"=="    {return EQ_T;}
"!="    {return NEQ_T;}
"<="    {return LEQ_T;}
">="    {return GEQ_T;}
[+*/<>();=-]    {return *yytext;}
[ \t\n] { }
.       {
            std::cerr << "Leksicka greska: " <<(*yytext) << std::endl;
            exit(EXIT_FAILURE);
        }

%%