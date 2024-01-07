%option noyywrap

%{
  #include <iostream>
  #include <cstdio>
  #include <cstdlib>
  #include <string>

  using namespace std;

  #include "broj.hpp"
  #include "parser.tab.hpp"

%}

%%

int                    { return INT_T; }
print                  { return PRINT_T; }
list                   { return LIST_T; }

_[a-zA-Z][a-zA-Z0-9]*  {
			  yylval.ime = new string(yytext);
			  return ID;
                       }
"=="                   { return EQ_T;    }
"!="                   { return NEQ_T;   }
"<<"                   { return SHL_T;   }
">>"                   { return SHR_T;   }
"+"                    { return PLUS_T;  }
"-"                    { return MINUS_T; }

[*/%\[\]()=,;&|^~\n]   { return *yytext; }

0x[a-fA-F0-9]+	{
		  yylval.x = strtol(yytext, NULL, 16);
		  return BROJ;
		}
0[0-7]+   {
	    yylval.x = strtol(yytext, NULL, 8);
	    return BROJ;
	  } 
[0-9]+	  {
	    yylval.x = strtol(yytext, NULL, 10);
	    return BROJ;
	  }
[ \t]	  { }
.         {
	    cerr << "Leksicka greska. Ne prepoznat token " << yytext << "!" << endl;
	    exit(EXIT_FAILURE);
          }

%%
