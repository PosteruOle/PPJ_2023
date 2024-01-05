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

"list"                { return LIST; }
"number"              { return NUMBER; }
"string"              { return STRING; }
"print"               { return PRINT; }
"print_r"             { return PRINT_R; }
["]([^"]|\\["])*["]   { return REAL_STRING; }
[a-zA-Z_][a-zA-Z0-9]* { return ID; }
[0-9]+(\.[0-9]+)?     { return BROJ; }
[-+*/<>();,.{}=]      { return *yytext; }
[ \n\t]               { }
.                     { 
    cerr << "Leksicka greska! Neprepoznat token: " << yytext << endl;
    exit(EXIT_FAILURE);
}

%%