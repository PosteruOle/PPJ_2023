%option noyywrap
%option noinput
%option nounput

%{
    #include <iostream>
    #include <cstdlib>
    #include <string>
    #include <vector>
    #include "polinomi.hpp"

    using namespace std;

    #include "parser.tab.hpp"
%}

%%

[a-zA-Z_][a-zA-Z_0-9]* { 
    yylval.id=new string(yytext);
    return ID; 
}
[+-]?[0-9]+(\.[0-9]+)? { 
    yylval.x=atof(yytext);
    return BROJ; 
}
":="                   { return DODELA; }
"=="                   { return EQ; }
"!="                   { return NEQ; }
[-+*<>()\[\],'$|\n]    { return *yytext; }
[ \t]                  { }
.                      {
    cerr << "Leksicka greska! Neprepoznat token: " << yytext << endl;
    exit(EXIT_FAILURE);
}

%%