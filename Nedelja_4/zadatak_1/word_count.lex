%option noyywrap

%{
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  
  int brojLinija=0;
  int brojKaraktera=0;
%}


%%

.           { brojKaraktera++; }
\n          { brojKaraktera++; brojLinija++;}


%%

int main(int argc, char *argv[]){

   //yyin 
   //yyout
   if(argc>=2){
     yyin=fopen(argv[1], "r");
     if(yyin==NULL){
       exit(EXIT_FAILURE);
     }
   }
   
   yylex();
   printf("Broj linija iznosi %d.\n", brojLinija);
   printf("Broj karaktera iznosi %d.\n", brojKaraktera);
   
   if(yyin!=stdin){
     fclose(yyin);
   }

   return 0;
}


