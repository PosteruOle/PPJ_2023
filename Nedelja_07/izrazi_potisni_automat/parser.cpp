/*
Ovaj fajl sadrzi rucnu implementaciju sintaksnog analizatora koriscenjem tehnike potisnog automata.
Kreirani sintaksni analizator ce biti u stanju da proveri da li je samo JEDAN aritmeticki izraz u skladu sa gramatikom izraza
koja od operacija podrzava samo +, * i grupisanje!
*/
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <stack>
#define YYDEBUG 1

using namespace std;

#include "tokeni.hpp"

extern int yylex();
stack<int> stek;
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

int main(){

    preduvid=yylex();
    stek.push(E);
    while(!stek.empty()){
        switch(stek.top()){
            /* Gramatika:           Skupovi izbora
            * E  -> T EP           { OZ,BROJ }
            */
            case E: 
                if(preduvid==OZ || preduvid==BROJ){
                    stek.pop();
                    stek.push(EP);
                    stek.push(T);
                } else {
                    cerr << "Sintaksna greska! E\n";
                    exit(EXIT_FAILURE);
                }
                break;
            /* Gramatika:           Skupovi izbora
            * EP -> + T EP         { PLUS }
            *      | eps           { EOI, ZZ }
            */    
            case EP:
                if(preduvid==PLUS){
                    stek.pop();
                    stek.push(EP);
                    stek.push(T);
                    stek.push(PLUS);
                } else if(preduvid==EOI || preduvid==ZZ){
                    stek.pop();
                } else {
                    cerr << "Sintaksna greska! EP\n";
                    exit(EXIT_FAILURE);
                }
                break;
            /* Gramatika:           Skupovi izbora
            * T  -> F TP           { OZ, BROJ }
            */    
            case T:
                if(preduvid==OZ || preduvid==BROJ){
                    stek.pop();
                    stek.push(TP);
                    stek.push(F);
                } else {
                    cerr << "Sintaksna greska! T\n";
                    exit(EXIT_FAILURE);
                }
                break;
            /* Gramatika:           Skupovi izbora
            * TP -> * F TP         { PUTA }
            *      | eps           { PLUS, ZZ, EOI }
            */     
            case TP:
                if(preduvid==PUTA){
                    stek.pop();
                    stek.push(TP);
                    stek.push(F);
                    stek.push(PUTA);
                } else if(preduvid==PLUS || preduvid==ZZ || preduvid==EOI){
                    stek.pop();
                } else {
                    cerr << "Sintaksna greska! TP\n";
                    exit(EXIT_FAILURE);
                }
                break;
            /* Gramatika:           Skupovi izbora
            * F  -> ( E )          { OZ }
            *      | BROJ          { BROJ }
            */    
            case F:
                if(preduvid==OZ){
                    stek.pop();
                    stek.push(ZZ);
                    stek.push(E);
                    stek.push(OZ);
                } else if(preduvid==BROJ){
                    stek.pop();
                    stek.push(BROJ);
                } else {
                    cerr << "Sintaksna greska! F\n";
                    exit(EXIT_FAILURE);
                }
                break;
            default:
                if(preduvid==stek.top()){
                    stek.pop();
                    preduvid=yylex();
                } else {
                    cerr << "Sintaksna greska! DEFAULT\n";
                    exit(EXIT_FAILURE);
                }
                break;                
        }
    }
    cout << "Sve je u redu sa unetim izrazom!\n";

    return 0;
}
