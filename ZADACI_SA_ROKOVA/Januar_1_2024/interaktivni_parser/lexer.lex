%option noyywrap

%{
    #include <iostream>
    #include <cstdlib>
    #include <vector>
    #include <string>

    using namespace std;

    #include "parser.tab.hpp"
%}

%%

"def"                  { return DEF; }
"print"                { return PRINT; }
"%d"                   { return PD; }
"%h"                   { return PH; }
"%b"                   { return PB; }
[a-zA-Z_][a-zA-Z_0-9]* { 
    yylval.id=new string(yytext);
    return ID; 
}
"<<"                   { return SL; }
">>"                   { return SR; } 
"=="                   { return EQ; }
"!="                   { return NEQ; }
">="                   { return GEQ; }
"<="                   { return LEQ; }
[0-9]+                 { 
    yylval.x=atoi(yytext);
    return BROJ; 
}
[-+*/()=",;|&^%~<>]    { return *yytext; }
[ \t\n]                { }
.                      {
    cerr << "Leksicka greska! Neprepoznat token: " << yytext << endl;
    exit(EXIT_FAILURE);
}

%%