%option noyywrap

%{
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  
  #define KLJUCNA_REC   (1)
  #define INTERPUNKCIJA (2)
  #define ID            (3)
  #define I_CONST       (4)
  #define F_CONST       (5)
  #define DODELA        (6)
  #define AO            (7)
  #define RO            (8)
  #define OZ            (9)
  #define ZZ            (10)
%}

%%

if|then|else|begin|end|integer|var { return KLJUCNA_REC; }
[a-zA-Z_][a-zA-Z0-9_]*             { return ID; }
[-+*/]                             { return AO; }
[,.:;]                             { return INTERPUNKCIJA; }
"("                                { return OZ; }
")"                                { return ZZ; }
"<"|">"|">="|"<="                  { return RO; }
[+-]?[0-9]+                        { return I_CONST; }
[+-]?[0-9]+\.[0-9]+                { return F_CONST; }
":="                               { return DODELA; }
[ \t\n]                            { }
.                                  {
                                     fprintf(stderr, "Leksicka greska! Neprepoznat token: %s\n", yytext);
                                     exit(EXIT_FAILURE);
                                   }

%%

int main(){

   int token=0;
    while((token=yylex())){
        switch(token){
            case ID: 
                printf("Pronadjen je identifikator: %s\n", yytext);
                break;
            case AO:
                printf("Pronadjen je aritmeticki operator: %s\n", yytext);
                break;
            case RO:
                printf("Pronadjen je relacioni operator: %s\n", yytext);
                break;    
            case OZ:
                printf("Pronadjena je otvorena zagrada: %s\n", yytext);
                break;                
            case ZZ:
                printf("Pronadjena je zatvorena zagrada: %s\n", yytext);
                break;    
            case KLJUCNA_REC:
                printf("Pronadjena je kljucna rec: %s\n", yytext);
                break;
            case INTERPUNKCIJA:
                printf("Pronadjen je znak interpunkcije: %s\n", yytext);
                break;
            case I_CONST:
                printf("Pronadjen je ceo broj: %s\n", yytext);
                break;
            case F_CONST:
                printf("Pronadjen je realan broj: %s\n", yytext);
                break;    
            case DODELA:
                printf("Pronadjen je znak za dodelu: %s\n", yytext);
                break;
        }
    }

   return 0;
}
