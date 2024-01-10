%option noyywrap
%option noinput
%option nounput

%{
    #include <iostream>
    #include <cstdlib>
    #include <string>
    #include "tokeni.hpp"

    using namespace std;
%}

%%

"broj"                  { return BROJ_T; }
"sqrt"                  { return SQRT; }
"stampaj"               { return STAMPAJ; }
":="                    { return DODELA; }
[a-zA-Z_][a-zA-Z_0-9]*  { return ID; }
[+-]?[0-9]+(\.[0-9]+)?  { return BROJ; }
[-+*/,;()]              { return *yytext; }
[ \t\n]                 { }
.                       {
    cerr << "Leksicka greska! Neprepoznat token: " << yytext << endl;
    exit(EXIT_FAILURE);
}

%%