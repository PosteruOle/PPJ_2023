%option noyywrap

%{
   #include <stdio.h>
   #include <stdlib.h>
   
   int brojOtvorenih=0;
%}


%%

"("    { ECHO; brojOtvorenih++; }
")"    { 
         ECHO; //printf("%s", yytext);
         brojOtvorenih--;
         if(brojOtvorenih<0)
           return -1;
       }
      

%%

int main(){

   int token=yylex();
   if(token<0){
     printf("Zagrade nisu ispravno uparene!\n");
     exit(EXIT_FAILURE);
   }
   
   if(brojOtvorenih==0){
     printf("Zagrade su ispravno uparene!\n");
   } else {
     printf("Zagrade nisu ispravno uparene!\n");
   }

   return 0;
}
