%option noyywrap
%{
    #include <iostream>
    #include <cstdlib>
    #include <string>
    #include <vector>

    using namespace std;

    #include "tokeni.hpp"
%}

%%

"print_ALL"             { return PRINTALL; }
[a-zA-Z_][a-zA-Z0-9]*   { return ID; } 
[+-]?[0-9]+             { return BROJ; }
":="                    { return DODELA; }
"["                     { return OZ; }
"]"                     { return ZZ; }
";"                     { return TZ; }
\n                      { return N; }
[ \t]                   { }
.                       {
    cerr << "Leksicka greska! Neprepoznat token: " << yytext << endl;
    exit(EXIT_FAILURE);
}

%%