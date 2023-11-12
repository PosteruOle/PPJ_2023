/*
Ovaj fajl sadrzi rucnu implementaciju sintaksnog analizatora koriscenjem tehnike rekurzivnog spusta.
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
int preduvid=0;
int broj_deklaracija=0;

/*  Gramatika:                                           Skupovi izbora
 *  niz_deklaracija -> deklaracija TZ niz_deklaracija    { EL_TIP, ID}
 *  | eps                                                { EOI }
 *  deklaracija -> tip niz_promenljivih TZ               { EL_TIP, ID }
 *  tip -> EL_TIP tip_prim                               { EL_TIP }
 *  | ID tip_prim                                        { ID }
 *  tip_prim -> OZ ZZ tip_prim                           { OZ }
 *            | eps                                      { ID }
 *  niz_promenljivih -> ID niz_promenljvih_prim          { ID }
 *  niz_promenljivih_prim -> Z ID niz_promenljivih_prim  { Z }
 *  | eps                                                { TZ }                                                 
 */

void niz_deklaracija();
void deklaracija();
void tip();
void tip_prim();
void niz_promenljivih();
void niz_promenljivih_prim();

int main(){

    preduvid=yylex();
    niz_deklaracija();
    if(preduvid==EOI){
        cout << "Sve je u redu sa unetim deklaracijama!\n";
    } else {
        cerr << "Sintaksna greska! Visak tokena na ulazu!\n";
        exit(EXIT_FAILURE);
    }

    return 0;
}

/*  Gramatika:                                           Skupovi izbora
 *  niz_deklaracija -> deklaracija TZ niz_deklaracija    { EL_TIP, ID}
 *  | eps                                                { EOI }                                                 
 */
void niz_deklaracija(){
    if(preduvid==EL_TIP || preduvid==ID){
        deklaracija();
        broj_deklaracija++;
        cout << "Obradjena je " << broj_deklaracija << ". po redu deklaracija!\n";
        if(preduvid!=TZ){
           cerr << "Sintaksna greska neobavezna! (NIZ_DEKLARACIJA)\n";
            exit(EXIT_FAILURE); 
        }
        preduvid=yylex();
        niz_deklaracija();
    } else if(preduvid==EOI){
        return;
    } else {
        cerr << "Sintaksna greska! (NIZ_DEKLARACIJA)\n";
        exit(EXIT_FAILURE);
    }
}

/*  Gramatika:                                           Skupovi izbora
 *  deklaracija -> tip niz_promenljivih                  { EL_TIP, ID }                                                 
 */
void deklaracija(){
    if(preduvid==EL_TIP || preduvid==ID){
        tip();
        niz_promenljivih();
    } else {
        cerr << "Sintaksna greska! (DEKLARACIJA)\n";
        exit(EXIT_FAILURE);
    }
}

/*  Gramatika:                                           Skupovi izbora
 *  tip -> EL_TIP tip_prim                               { EL_TIP }
 *  | ID tip_prim                                        { ID }                                                
 */
void tip(){
    if(preduvid==EL_TIP){
        preduvid=yylex();
        tip_prim();
    } else if(preduvid==ID){
        preduvid=yylex();
        tip_prim();
    } else {
        cerr << "Sintaksna greska! (TIP)\n";
        exit(EXIT_FAILURE);
    }
}

/*  Gramatika:                                           Skupovi izbora
 *  tip_prim -> OZ ZZ tip_prim                           { OZ }
 *            | eps                                      { ID }                                                
 */
void tip_prim(){
    if(preduvid==OZ){
        preduvid=yylex();
        preduvid=yylex();
        tip_prim();
    } else if(preduvid==ID){
        return;
    } else {
        cerr << "Sintaksna greska! (TIP_PRIM)\n";
        exit(EXIT_FAILURE);
    }
}

/*  Gramatika:                                           Skupovi izbora
 *  niz_promenljivih -> ID niz_promenljvih_prim          { ID }                                               
 */
void niz_promenljivih(){
    if(preduvid==ID){
        preduvid=yylex();
        niz_promenljivih_prim();
    } else {
        cerr << "Sintaksna greska! (NIZ_PROMENLJIVIH)\n";
        exit(EXIT_FAILURE);
    }
}

/*  Gramatika:                                           Skupovi izbora
 *  niz_promenljivih_prim -> Z ID niz_promenljivih_prim  { Z }
 *  | eps                                                { TZ }                                                 
 */
void niz_promenljivih_prim(){
    if(preduvid==Z){
        preduvid=yylex();
        preduvid=yylex();
        niz_promenljivih_prim();
    } else if(preduvid==TZ){
        return;
    } else {
        cerr << "Sintaksna greska! (NIZ_PROMENLJIVIH_PRIM)\n";
        exit(EXIT_FAILURE);
    }
}
