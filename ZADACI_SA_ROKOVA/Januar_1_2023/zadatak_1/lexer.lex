%option noyywrap
%option noinput
%option nounput

%{
    #include <iostream>
    #include <cstdlib>
    #include <string>
    #include <vector>

    using namespace std;

    #include "parser.tab.hpp"
%}

%%

"sifra"                 { return SIFRA; }
"stampaj"               { return STAMPAJ; }
"lista_sifri"           { return LISTASIFRI; }
"sum()"                 { return SUM; }
"fst"                   { return FIRST; }
"snd"                   { return SECOND; }
[a-zA-Z_][a-zA-Z_0-9]*  { 
    yylval.id=new string(yytext);
    return ID; 
}
[-]?[0-9]+(\.[0-9]+)?  { 
    yylval.x=atof(yytext);
    return BROJ; 
}
"=="                    { return EQ; }
"!="                    { return NEQ; }
[-+*/,.;=()\[\]?]       { return *yytext; }
[ \t\n]                 { }
.                       {
    cerr << "Leksicka greska! Neprepoznat token: " << yytext << "( "<< *yytext- '0' << " )"<< endl;
    exit(EXIT_FAILURE);
}


%%