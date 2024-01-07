%option noyywrap

%{
  #include <stdio.h>
  #include <stdlib.h>
  #include "tokeni.h"
%}

%%
int                     { return INT; }
print                   { return PRINT; }
_[a-zA-Z][a-zA-Z0-9]*   { return ID; }
[0-9]+                  { return BROJ; }
"|"                     { return ILI; }
"&"                     { return III; }
"("                     { return OZ; }
")"                     { return ZZ; }
"~"                     { return INV; }
"="                     { return DODELA; }
[\n]                    { return NL; }
[ \t]                   { }
.                       {
                          fprintf(stderr, "Leksicka greska!\n"); 
                          exit(EXIT_FAILURE);
                        }

%%
