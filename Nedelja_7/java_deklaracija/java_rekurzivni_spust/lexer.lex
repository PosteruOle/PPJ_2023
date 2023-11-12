%option noyywrap

%{
    #include <iostream>
    #include <cstdlib>
    #include <string>

    using namespace std;

    #include "tokeni.hpp"
%}

%%

"double"|"float"|"char"|"int" { return EL_TIP; }
[a-zA-Z_][a-zA-Z_0-9]*        { return ID; }
","                           { return Z; }
";"                           { return TZ; }
"]"                           { return ZZ; }
"["                           { return OZ; }
[ \n\t]                       { }
.                             {
    cerr << "Leksicka greska!Neprepoznat token" << yytext << "\n";
    exit(EXIT_FAILURE);
}

%%