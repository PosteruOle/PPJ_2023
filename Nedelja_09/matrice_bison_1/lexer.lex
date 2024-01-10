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

"print_ALL"            { return PRINTALL; }
[a-zA-Z_][a-zA-Z_0-9]* { 
    yylval.id=new string(yytext);
    return ID; 
}
[+-]?[0-9]+            { 
    yylval.x=atoi(yytext);
    return BROJ; 
}
".*"                   { return PKM; }
":="                   { return DODELA; }
[-+*\[\](),;'\n]       { return *yytext; }
[ \t]                  { }
.                      {
    cerr << "Leksicka greska! Neprepoznat token: " << yytext << endl;
    exit(EXIT_FAILURE);
}

%%