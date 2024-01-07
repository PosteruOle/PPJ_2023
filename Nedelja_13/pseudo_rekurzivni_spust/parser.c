/*
 * Naivna gramatika:
 * program -> program naredba '\n'
 * 	    | naredba '\n'
 * naredba -> INT_T ID = E 
 * 	    | PRINT '(' E ')' 
 * 	    | E 
 * E -> E | T
 *    | T
 * T -> T & F
 *    | F
 * F -> ~ G
 *    | G
 * G -> BROJ
 *    | '(' E ')'
 * ----------------------------------------------------------------------------------------------------------
 * Eliminacija leve rekurzije:
 * Gramatika:									Skupovi izbora:
 * program -> naredba '\n' programP				                INT, PRINT, ~, BROJ, (
 * programP -> naredba '\n' programP				                INT, PRINT, ~, BROJ, (
 * 	     | eps								EOI
 * naredba -> INT_T ID = E 						        INT
 * 	    | PRINT '(' E ')' 					                PRINT
 * 	    | E 							        ~, BROJ, (
 * E -> T EP									~, BROJ, (				
 * EP -> | T EP								|
 *     | eps								        \n, )
 * T -> F TP									~, BROJ, (
 * TP -> & F TP								&
 *     | eps								        |, \n, )
 * F -> ~ G									~
 *    | G								        BROJ, (
 * G -> BROJ									BROJ
 *    | '(' E ')'								(
 * 
 * Skupovi izbora		First					Eps		Follow
 * program			INT, PRINT, ~, BROJ, (		        NE		EOI
 * programP			INT, PRINT, ~, BROJ, (		        DA		EOI
 * naredba			INT, PRINT, ~, BROJ, (		        NE		;
 * E				~, BROJ, (				NE		;, )
 * EP				|					DA		;, )
 * T				~, BROJ, (				NE		|, ;, )
 * TP				&					DA	 	|, ;, )
 * F				~, BROJ, (				NE		&, |, ;, )
 * G				BROJ, (				NE		&, |, ;, )
 */
#include <stdio.h>
#include <stdlib.h>
#include "tokeni.h"

extern int yylex();
int preduvid;

void program(void);
void programP(void);
void naredba(void);
void E(void);
void T(void);
void TP(void);
void EP(void);
void F();
void G();

int main() {
	
   preduvid = yylex();
   program();
   
   if(preduvid == EOI) {
     printf("Sve je okej\n");
   } else {
     fprintf(stderr, "Sintaksna greska! Visak tokena na ulazu!\n");
     exit(EXIT_FAILURE);
   }
   
   exit(EXIT_SUCCESS);
}

/*
 * Gramatika:									Skupovi izbora:
 * program -> naredba '\n' programP				                INT, PRINT, ~, BROJ, (
 */
void program(void) {
   if(preduvid==INT || preduvid==PRINT || preduvid==INV || preduvid==BROJ || preduvid==OZ){
     naredba();
     preduvid==yylex();
     programP();
   } else {
     fprintf(stderr,"Sintaksna greska! Ocekivani tokeni INT, PRINT, INV, BROJ ili OZ!\n");
     exit(EXIT_FAILURE);
   }	
}

/*
 * Gramatika:									Skupovi izbora:
 * programP -> naredba '\n' programP				                INT, PRINT, ~, BROJ, (
 * 	     | eps								EOI
 */
void programP(void) {
   if(preduvid==INT || preduvid==PRINT || preduvid==INV || preduvid==BROJ || preduvid==OZ){
     naredba();
     preduvid==yylex();
     programP();
   } else if(preduvid==EOI){
     return;
   } else {
     fprintf(stderr,"Sintaksna greska! Ocekivani tokeni INT, PRINT, INV, BROJ, OZ ili EOI!\n");
     exit(EXIT_FAILURE);
   }	
}

/*
 * Gramatika:									Skupovi izbora:
 * naredba -> INT ID = E 						        INT
 * 	    | PRINT '(' E ')' 					                PRINT
 * 	    | E 							        ~, BROJ, (
 */
void naredba(void) {
   if(preduvid==INT){
     preduvid==yylex();
     preduvid==yylex();
     preduvid==yylex();
     E();
   } else if(preduvid==PRINT){
     preduvid==yylex();
     preduvid==yylex();
     E();
     preduvid==yylex();
   } else if(preduvid==INV || preduvid==BROJ || preduvid==OZ){
     E();
   } else {
     fprintf(stderr,"Sintaksna greska! Ocekivani tokeni INT, PRINT, INV, BROJ ili OZ!\n");
     exit(EXIT_FAILURE);
   }	
}

/*
 * Gramatika:									Skupovi izbora:
 * E -> T EP									~, BROJ, (				
 */
void E(void) {
  if(preduvid==INV || preduvid==BROJ || preduvid==OZ){
    T();
    EP();
  } else {
    fprintf(stderr,"Prosledjen je token %d!\n", preduvid);
    fprintf(stderr,"Sintaksna greska! Ocekivani tokeni INV, BROJ ili OZ!\n");
    fprintf(stderr,"Neterminal E!\n");
    exit(EXIT_FAILURE);
  }	
}
/*
 * Gramatika:									Skupovi izbora:
 * T -> F TP									~, BROJ, (
 */
void T(void) {
   if(preduvid==INV || preduvid==BROJ || preduvid==OZ){
     F();
     TP();
   } else {
     fprintf(stderr,"Prosledjen je token %d!\n", preduvid);
     fprintf(stderr,"Sintaksna greska! Ocekivani tokeni INV, BROJ ili OZ!\n");
     fprintf(stderr,"Neterminal T!\n");
     exit(EXIT_FAILURE);
   }	
}

/*
 * Gramatika:									Skupovi izbora:
 * TP -> & F TP								&
 *     | eps								        |, \n, )
 */
void TP(void) {
   if(preduvid==III){
     preduvid==yylex();
     F();
     TP();
   } else if(preduvid==ILI || preduvid==NL || preduvid==ZZ){
     return;
   } else {
     fprintf(stderr,"Prosledjen je token %d!\n", preduvid);
     fprintf(stderr,"Sintaksna greska! Ocekivani tokeni III, ILI, NL ili ZZ!\n");
     fprintf(stderr,"Neterminal TP!\n");
     exit(EXIT_FAILURE);
   }	
}

/*
 * Gramatika:									Skupovi izbora:			
 * EP -> | T EP								|
 *     | eps								        \n, )
 */
void EP(void) {
   if(preduvid==ILI){
     preduvid==yylex();
     T();
     EP();
   } else if(preduvid==NL || preduvid==ZZ){
     return;
   } else {
     fprintf(stderr,"Sintaksna greska! Ocekivani tokeni ILI, NL ili ZZ!\n");
     fprintf(stderr,"Neterminal EP!\n");
     exit(EXIT_FAILURE);
   }	
}

/*
 * Gramatika:									Skupovi izbora:
 * F -> ~ G									~
 *    | G								        BROJ, (
 */
void F() {
   if(preduvid==INV){
     preduvid==yylex();
     G();
   } else if(preduvid==BROJ || preduvid==OZ){
     G();
   } else {
     fprintf(stderr,"Sintaksna greska! Ocekivani tokeni INV, BROJ ili OZ!\n");
     fprintf(stderr,"Neterminal F!\n");
     exit(EXIT_FAILURE);
   }	
}

/*
 * Gramatika:									Skupovi izbora:
 * G -> BROJ									BROJ
 *    | '(' E ')'								(
 */
void G() {
  if(preduvid==BROJ){
    preduvid==yylex();
    return;
  } else if(preduvid==OZ){
    preduvid==yylex();
    E();
    preduvid==yylex();
  } else {
    fprintf(stderr,"Sintaksna greska! Ocekivani tokeni BROJ ili OZ!\n");
    exit(EXIT_FAILURE);
  }	
}

