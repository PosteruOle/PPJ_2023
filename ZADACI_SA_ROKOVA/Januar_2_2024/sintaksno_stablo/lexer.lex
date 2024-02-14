%option noyywrap
%option nounput
%option noinput

%{
  #include <iostream>
  #include <cstdlib>
  #include <string>
  #include "izrazi.hpp"
  #include "naredbe.hpp"
  
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
"if"                   { return IF; }
"else"                 { return ELSE; }
"while"                { return WHILE; }
["]([^"]|\\["])*["]    { 
  yylval.id=new string(yytext);
  return MESSAGE; 
}
[a-zA-Z_][a-zA-Z_0-9]* { 
  yylval.id=new string(yytext);
  return ID; 
}
"=="                   { return EQ; }
"!="                   { return NEQ; }
[+*();:.,=\[\]{}"~]    { return *yytext; }
"<<"                   { return MM; }
">>"                   { return VV; }
[ \t\n]                { }
.                      {
  cerr << "Leksicka greska! Neprepoznat token: " << yytext << endl;
}  

%%