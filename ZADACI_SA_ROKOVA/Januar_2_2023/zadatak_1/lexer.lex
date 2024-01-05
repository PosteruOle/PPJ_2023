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

"list"                { return LIST; }
"number"              { return NUMBER; }
"string"              { return STRING; }
"print"               { return PRINT; }
"print_r"             { return PRINT_R; }
"push_back"           { return PUSH_BACK; }
"push_front"          { return PUSH_FRONT; }
"push"                { return PUSH; }
"get"                 { return GET; }
"find"                { return FIND; }
"=="                  { return EQ; }
"!="                  { return NEQ; }
"<="                  { return LEQ; }
">="                  { return GEQ; }
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