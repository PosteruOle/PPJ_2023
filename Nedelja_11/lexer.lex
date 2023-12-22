%option noyywrap
%option noinput
%option nounput

%{
    #include <iostream>
    #include <cstdlib>
    #include <string>
    #include <vector>
    #include "izrazi.hpp"
    #include "naredba.hpp"

    using namespace std;

    #include "parser.tab.hpp"
%}

%%

"pocetak"         { return POCETAK; }
"kraj"            { return KRAJ; }
"ispisi"          { return ISPISI; }
"unesi"           { return UNESI; }
"ako_je"          { return AKOJE; }
"onda"            { return ONDA; }
"inace"           { return INACE; }
"dok_je"          { return DOKJE; }
"radi_sledece"    { return RADISLEDECE; }
"mod"             { return MOD; } 
":="              { return DODELA; }
["]([^"]|\\["])*["]    { 
    yylval.id=new string(yytext);
    return STRING; 
}
[a-zA-Z_][a-zA-Z_0-9]* { 
    yylval.id=new string(yytext);
    return ID; 
}
[0-9]+(\.[0-9]*)?  { 
    yylval.x=atof(yytext);
    return BROJ; 
}
"0x"[0-9A-Fa-f]*  { 
    yylval.x=strtol(yytext, &yytext, 16);
    return H_BROJ; 
}
[<>;:(),./+*-]    { return *yytext; }
"<="              { return LEQ; }
">="              { return GEQ; }
"=="              { return EQ; }
"!="              { return NEQ; }
[ \t\n]           { }
.                 {
    cerr << "Leksicka greska! Neprepoznat token: " << yytext << endl;
    exit(EXIT_FAILURE);
} 

%%