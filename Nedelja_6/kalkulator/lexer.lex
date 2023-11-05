%option noyywrap

%{
    #include <iostream>
    #include <cstdlib>

    using namespace std;

    #include "parser.tab.hpp"
%}

%%

"print"                  { return PRINT; }
"print_ALL"              { return PRINT_ALL; }
[a-zA-Z_][a-zA-Z_0-9]*   { 
    yylval.s=new string(yytext);
    return ID; 
}
[0-9]+(\.[0-9]+)?        { 
    yylval.x=atof(yytext);
    return BROJ; 
}
[-+*/();,.<>]            { return *yytext; }
":="                     { return DODELA; }
"<="                     { return LEQ; }
">="                     { return GEQ; }
"=="                     { return EQ; }
"!="                     { return NEQ; }
[ \n\t]                  { }
.                        {
    cerr << "Leksicka greska! Neprepoznat token: " << yytext << endl;
    exit(EXIT_FAILURE);
}

%%