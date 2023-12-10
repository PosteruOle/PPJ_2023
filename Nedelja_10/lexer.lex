%option noyywrap

%{
    #include <iostream>
    #include <cstdlib>
    #include <string>
    #include <vector>
    #include "funkcije.hpp"

    using namespace std;

    #include "parser.tab.hpp"
%}

%%

"print_ALL"          { return PRINTALL; }
"function"           { return FUNCTION; }
"sin"                { return SIN; }
"cos"                { return COS; }
[A-Z]                { 
    yylval.c=*yytext;
    return FID; 
}
[a-z]                {
    yylval.c=*yytext; 
    return ID; 
}
[0-9]+(\.[0-9]+)?    {
    yylval.x=atof(yytext); 
    return BROJ; 
}
[-+*/();=,"'<>\[\]\n] { return *yytext; } 
[ \t]                { }
.                    {
    cerr << "Leksicka greska! Neprepoznat token: " << yytext << endl;
    exit(EXIT_FAILURE);
}

%%