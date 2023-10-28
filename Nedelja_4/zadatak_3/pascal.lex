%option noyywrap

%{
  #include <stdio.h>
  #include <stdlib.h>
  
%}


%%

"{".*?"}"     { }
"(*"([^*]|\*+[^)])*\*+")"  { }


%%

int main(){

  yylex();

  return 0;
}
