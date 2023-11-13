/*
Ovaj fajl sadrzi rucnu implementaciju sintaksnog analizatora koriscenjem tehnike rekurzivnog spusta.
Kreirani sintaksni analizator ce biti u stanju da proveri da li je samo JEDAN aritmeticki izraz u skladu sa gramatikom izraza
koja od operacija podrzava samo +, * i grupisanje!
*/
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#define YYDEBUG 1

using namespace std;

#include "tokeni.hpp"

extern int yylex();
int preduvid=0;

/* Gramatika:           Skupovi izbora
 * E  -> T EP           { OZ,BROJ }
 * EP -> + T EP         { PLUS }
 *      | eps           { EOI, ZZ }
 * T  -> F TP           { OZ, BROJ }
 * TP -> * F TP         { PUTA }
 *      | eps           { PLUS, ZZ, EOI }
 * F  -> ( E )          { OZ }
 *      | BROJ          { BROJ }
 */

void E();
void EP();
void T();
void TP();
void F();

int main(){

    preduvid=yylex();
    E();
    if(preduvid==EOI){
        cout << "Sve je u redu sa unetim izrazom!\n";
    } else {
        cerr << "Sintaksna greska! Visak tokena na ulazu!\n";
        exit(EXIT_FAILURE);
    }

    return 0;
}

/* Gramatika:           Skupovi izbora
 * E  -> T EP           { OZ,BROJ }
 */
void E(){

    #ifdef YYDEBUG
    cout << "E  -> T EP\n";
    #endif

    if(preduvid==OZ || preduvid==BROJ){
        T();
        EP();
    } else {
        cerr << "Sintaksna greska! E\n";
        exit(EXIT_FAILURE);
    }
}

/* Gramatika:           Skupovi izbora
 * EP -> + T EP         { PLUS }
 *      | eps           { EOI, ZZ }
 */
void EP(){
    if(preduvid==PLUS){
        #ifdef YYDEBUG
        cout << "EP -> + T EP\n";  
        #endif
        preduvid=yylex();
        T();
        EP();
    } else if(preduvid==EOI || preduvid==ZZ){
        #ifdef YYDEBUG
        cout << "EP -> eps\n";  
        #endif
        return;
    } else {
        cerr << "Sintaksna greska! EP\n";
        exit(EXIT_FAILURE);
    }
}


/* Gramatika:           Skupovi izbora
 * T  -> F TP           { OZ, BROJ }
 */
void T(){
    if(preduvid==OZ || preduvid==BROJ){
        #ifdef YYDEBUG
        cout << "T  -> F TP\n";  
        #endif
        F();
        TP();
    } else {
        cerr << "Sintaksna greska! T\n";
        exit(EXIT_FAILURE);
    }
}

/* Gramatika:           Skupovi izbora
 * TP -> * F TP         { PUTA }
 *      | eps           { PLUS, ZZ, EOI }
 */
void TP(){
    if(preduvid==PUTA){
        #ifdef YYDEBUG
        cout << "TP -> * F TP\n";
        #endif
        preduvid=yylex();
        F();
        TP();
    } else if(preduvid==PLUS || preduvid==ZZ || preduvid==EOI){
        #ifdef YYDEBUG
        cout << "TP -> eps\n";
        #endif
        return;
    } else {
        cerr << "Sintaksna greska! TP\n";
        exit(EXIT_FAILURE);
    }
}

/* Gramatika:           Skupovi izbora
 * F  -> ( E )          { OZ }
 *      | BROJ          { BROJ }
 */
void F(){
    if(preduvid==OZ){
        #ifdef YYDEBUG
        cout << "F  -> ( E )\n";
        #endif
        preduvid=yylex();
        E();
        if(preduvid!=ZZ){
            cerr << "Sintaksna greska! F\n";
            exit(EXIT_FAILURE);
        } else {
            preduvid=yylex();
        }
    } else if(preduvid==BROJ){
        #ifdef YYDEBUG
        cout << "F  -> BROJ\n";
        #endif
        preduvid=yylex();
    } else {
        cerr << "Sintaksna greska! E\n";
        exit(EXIT_FAILURE);
    }
}
