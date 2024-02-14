%option noyywrap
%option nounput
%option noinput

%{
  #include <iostream>
  #include <cstdlib>
  #include <string>

  using namespace std;

  #include "parser.tab.hpp"
%}

%%

"start"                { return START; }
"end"                  { return END; }
"std_input"            { return INPUT; }
"std_output"           { return OUTPUT; }
"std_error"            { return ERROR; }
"string"               { return STRING; }
"print_ALL"            { return PRINT_ALL; }
["]([^"]|\\["])*["]    { 
  yylval.id=new string(yytext);
  return MESSAGE; 
}
[a-zA-Z_][a-zA-Z_0-9]* { 
  yylval.id=new string(yytext);
  return ID; 
}
[+*();:.,={}"~]        { return *yytext; }
"<<"                   { return MM; }
">>"                   { return VV; }
[ \t\n]                { }
.                      {
  cerr << "Leksicka greska! Neprepoznat token: " << yytext << endl;
}  

%%