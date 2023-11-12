/*
Ovaj fajl sadrzi rucnu implementaciju sintaksnog analizatora koriscenjem tehnike potisnog automata.
Kreirani sintaksni analizator ce biti u stanju da proveri ispravnost deklaracije promenljivih razlicitog tipa u programskom jeziku Java.
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
int broj_deklaracija=0;

/*  Gramatika:                                           Skupovi izbora
 *  niz_deklaracija -> deklaracija TZ niz_deklaracija    { EL_TIP, ID}
 *  | eps                                                { EOI }
 *  deklaracija -> tip niz_promenljivih                  { EL_TIP, ID }
 *  tip -> EL_TIP tip_prim                               { EL_TIP }
 *  | ID tip_prim                                        { ID }
 *  tip_prim -> OZ ZZ tip_prim                           { OZ }
 *            | eps                                      { ID }
 *  niz_promenljivih -> ID niz_promenljvih_prim          { ID }
 *  niz_promenljivih_prim -> Z ID niz_promenljivih_prim  { Z }
 *  | eps                                                { TZ }                                                 
 */

int main(){

    preduvid=yylex();
    stek.push(niz_deklaracija);
    while(!stek.empty()){
        switch (stek.top()){
        /*  Gramatika:                                           Skupovi izbora
        *  niz_deklaracija -> deklaracija TZ niz_deklaracija    { EL_TIP, ID}
        *  | eps                                                { EOI }                                               
        */
        case niz_deklaracija:
            if(preduvid==EL_TIP || preduvid==ID){
                stek.pop();
                stek.push(niz_deklaracija);
                stek.push(TZ);
                stek.push(deklaracija);
            } else if(preduvid==EOI){
                stek.pop();
            } else {
                cerr << "Sintaksna greska!\n";
                exit(EXIT_FAILURE);
            }
            break;
        
        /*  Gramatika:                                           Skupovi izbora
        *  deklaracija -> tip niz_promenljivih                   { EL_TIP, ID }                                               
        */    
        case deklaracija: 
            if(preduvid==EL_TIP || preduvid==ID){
                stek.pop();
                stek.push(niz_promenljivih);
                stek.push(tip);
            } else {
                cerr << "Sintaksna greska!\n";
                exit(EXIT_FAILURE);
            }  
            break;
        
        /*  Gramatika:                                           Skupovi izbora
        *  tip -> EL_TIP tip_prim                               { EL_TIP }
        *  | ID tip_prim                                        { ID }                                              
        */
        case tip:
            if(preduvid==EL_TIP){
                stek.pop();
                stek.push(tip_prim);
                stek.push(EL_TIP);
            } else if(preduvid==ID){
                stek.pop();
                stek.push(tip_prim);
                stek.push(ID);
            } else {
                cerr << "Sintaksna greska!\n";
                exit(EXIT_FAILURE);
            }
            break;
        
        /*  Gramatika:                                           Skupovi izbora
        *  tip_prim -> OZ ZZ tip_prim                           { OZ }
        *            | eps                                      { ID }                                                 
        */
        case tip_prim:
            if(preduvid==OZ){
                stek.pop();
                stek.push(tip_prim);
                stek.push(ZZ);
                stek.push(OZ);
            } else if(preduvid==ID){
                stek.pop();
            } else {
                cerr << "Sintaksna greska!\n";
                exit(EXIT_FAILURE);
            }
            break;

        /*  Gramatika:                                           Skupovi izbora
        *  niz_promenljivih -> ID niz_promenljvih_prim          { ID }                                                
        */    
        case niz_promenljivih:
            if(preduvid==ID){
                stek.pop();
                stek.push(niz_promenljivih_prim);
                stek.push(ID);
            } else {
                cerr << "Sintaksna greska!\n";
                exit(EXIT_FAILURE);
            }
            break;

        /*  Gramatika:                                           Skupovi izbora
        *  niz_promenljivih_prim -> Z ID niz_promenljivih_prim  { Z }
        *  | eps                                                { TZ }                                                 
        */    
        case niz_promenljivih_prim:
            if(preduvid==Z){
                stek.pop();
                stek.push(niz_promenljivih_prim);
                stek.push(ID);
                stek.push(Z);
            } else if(preduvid==TZ){
                stek.pop();
            } else {
                cerr << "Sintaksna greska!\n";
                exit(EXIT_FAILURE);
            }
            break;                
        default:
            if(preduvid==stek.top()){
                stek.pop();
                preduvid=yylex();
            } else {
                cerr << "Sintaksna greska! (DEFAULT)\n";
                exit(EXIT_FAILURE);
            }
            break;
        }
    }

    cout << "Sve je u redu sa unetim nizom deklaracija!\n";

    return 0;
}
