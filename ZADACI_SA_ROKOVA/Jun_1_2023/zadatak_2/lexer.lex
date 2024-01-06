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

"stack"                { return STACK; }
"int"                  { return INT; }
"print_stack"          { return PRINT_STACK; }
":="                   { return DODELA; }   
_[a-zA-Z][a-zA-Z_0-9]* { return ID; }
[0-9]+                 { return BROJ; }
[(){},;<>]             { return *yytext; }
[ \t\n]                { }
.                      {
    cerr << "Leksicka greska! Neprepoznat token: " << yytext << endl;
    exit(EXIT_FAILURE);
}

%%