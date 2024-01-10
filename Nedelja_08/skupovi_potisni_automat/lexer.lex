%option noyywrap

%{
    #include <iostream>
    #include <cstdlib>
    #include <string>
    #include "tokeni.hpp"

    using namespace std;
%}

%%

"print"                  { return PRINT; }
[a-zA-Z_][a-zA-Z_0-9]*   { return ID; }
[+-]?[0-9]+              { return BROJ; }
":="                     { return DODELA; }
".."                     { return TT; } 
","                      { return ZAREZ; }
";"                      { return TZ; }
"{"                      { return OZ; }
"}"                      { return ZZ; }
[ \t\n]                  { }
.                        {
    cerr << "Leksicka greska! Neprepoznat token: " << yytext << endl;
    exit(EXIT_FAILURE); 
}

%%