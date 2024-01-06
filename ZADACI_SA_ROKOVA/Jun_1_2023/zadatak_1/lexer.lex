%option noyywrap
%option noinput
%option nounput

%{
    #include <iostream>
    #include <cstdlib>
    #include <string>
    #include <vector>
    #include <deque>

    using namespace std;

    #include "parser.tab.hpp"
%}

%%

"stack"                 { return STACK; }
"queue"                 { return QUEUE; }
"peek"                  { return PEEK; }
"size"                  { return SIZE; }
"pop"                   { return POP; }
"push"                  { return PUSH; }
"print_stack"           { return PRINT_STACK; }
"print_queue"           { return PRINT_QUEUE; }
"int"                   { return INT; }
_[a-zA-Z_][a-zA-Z_0-9]* { 
    yylval.id=new string(yytext);
    return ID; 
}
[0-9]+                  { 
    yylval.x=atoi(yytext);
    return BROJ; 
}
[-+<>(){};,.]           { return *yytext; }
":="                    { return DODELA; }
"=="                    { return EQ; }
"!="                    { return NEQ; }
[ \t\n]                 { }
.                       { 
    cerr << "Leksicka greska! Neprepoznat token: " << yytext << endl;
    exit(EXIT_FAILURE);
}

%%