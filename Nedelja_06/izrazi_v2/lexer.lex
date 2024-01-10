%option noyywrap

%{
    #include <iostream>
    #include <cstdlib>
    #include <string>
    #include <vector>

    using namespace std;

    #include "parser.tab.hpp"
%}

%%

[0-9]+      { 
    yylval.x=atof(yytext);
    return BROJ; 
}
[-()+*/;]   { return *yytext; }
[ \t\n]     { }
.           {
    cerr << "Leksicka greska! Neprepoznat token: " << yytext << endl;
    exit(EXIT_FAILURE);
}     

%%