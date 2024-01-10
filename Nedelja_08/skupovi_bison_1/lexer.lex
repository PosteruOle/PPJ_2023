%option noyywrap

%{
    #include <iostream>
    #include <cstdlib>
    #include <vector>
    #include <string>
    #include <map>
    #include <set>

    using namespace std;

    #include "parser.tab.hpp"
%}

%%

"print_ALL"             { return PRINTALL; }
"print"                 { return PRINT; }
"check"                 { return CHECK; }
"card"                  { return CARD; }
"UniversalSet"          { return UNIVERSE; }
".."                    { return TT; }
[a-zA-Z_][a-zA-Z_0-9]*  { 
    yylval.id=new string(yytext);
    return ID; 
}
[+-]?[0-9]+             { 
    yylval.x=atof(yytext);
    return BROJ; 
}
":="                    { return DODELA; }
[<>{};,:~]              { return *yytext; } 
"\\\/"                  { return UNIJA; }
"\/\\"                  { return PRESEK; }
"\\"                    { return RAZLIKA; }
"<>"                    { return SIMRAZLIKA; }
[ \t\n]                 { }
.                       {
    cerr << "Leksicka greska! Neprepoznat token: " <<  yytext << endl;
    exit(EXIT_FAILURE);
}

%%