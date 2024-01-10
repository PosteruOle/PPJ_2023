%option noyywrap
%option noinput
%option nounput

%{
  #include <stdio.h>
  #include <stdlib.h>
  
  #define I_CONST 1
  #define F_CONST 2
  
%}

DIGIT [0-9]

%%

[+-]?{DIGIT}+          { return I_CONST; }
[+-]?[0-9]+\.[0-9]*  { return F_CONST; }
.                    { }
\n                   { }

%%

int main(){

  int token=0;
  while((token=yylex())){
     switch(token){
       case I_CONST: printf("Pronadjena je int konstanta: %s.\n", yytext); break;
       case F_CONST: printf("Pronadjena je float konstanta: %s.\n", yytext); break;
     }
  }

  return 0;
}
