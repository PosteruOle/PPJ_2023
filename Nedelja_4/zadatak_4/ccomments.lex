%option noyywrap

%{
  #include <stdio.h>
  #include <stdlib.h>
  
%}

%x comment1
%x comment2

%%

"/*"            { BEGIN(comment1); }
<comment1>[^\n] { }
<comment1>\n    { }
<comment1>"*/"  { BEGIN(INITIAL); }

"//"            { BEGIN(comment2); }
<comment2>.     { }
<comment2>\n    { BEGIN(INITIAL); }

%%

int main(){

  yylex();

  return 0;
}
