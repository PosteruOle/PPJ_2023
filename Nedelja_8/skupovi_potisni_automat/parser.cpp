#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <stack>
#include "tokeni.hpp"

using namespace std;

extern int yylex();

/*
LL(1) gramatika:                             Skupovi izbora:
program -> naredba ';' programP              {ID, PRINT}

programP -> naredba ';' programP             {ID, PRINT}
| eps                                        {EOI}

naredba -> ID DODELA skup                    {ID}
| print skup                                 {PRINT}

skup -> { lista_elemenata }                  {'{'}
| BROJ .. BROJ                               {BROJ}
| ID                                         {ID}

lista_elemenata -> BROJ lista_elemenataP     {BROJ}

lista_elemenataP -> , BROJ lista_elemenataP  {','}
| eps                                        {'}'}
*/

int main(){

    stack<int> stek;
    int preduvid=yylex();
    stek.push(PROGRAM);
    while(!stek.empty()){
        switch(stek.top()){
            /*
            LL(1) gramatika:                             Skupovi izbora:
            program -> naredba ';' programP              {ID, PRINT}
            */
            case PROGRAM:
                if(preduvid==ID || preduvid==PRINT){
                    stek.pop();
                    stek.push(PROGRAMP);
                    stek.push(TZ);
                    stek.push(NAREDBA);
                } else {
                    cerr << "Sintaksna greska! PROGRAM\n";
                    exit(EXIT_FAILURE);
                }
                break;
            
            /*
            LL(1) gramatika:                             Skupovi izbora:
            programP -> naredba ';' programP             {ID, PRINT}
            | eps                                        {EOI}
            */    
            case PROGRAMP:
                if(preduvid==ID || preduvid==PRINT){
                    stek.pop();
                    stek.push(PROGRAMP);
                    stek.push(TZ);
                    stek.push(NAREDBA);
                } else if(preduvid==EOI){
                    stek.pop();
                } else {
                   cerr << "Sintaksna greska! PROGRAMP\n";
                    exit(EXIT_FAILURE); 
                }
                break;
            
            /*
            LL(1) gramatika:                             Skupovi izbora:
            naredba -> ID DODELA skup                    {ID}
            | print skup                                 {PRINT}
            */
            case NAREDBA:
                if(preduvid==ID){
                    stek.pop();
                    stek.push(SKUP);
                    stek.push(DODELA);
                    stek.push(ID);
                } else if(preduvid==PRINT){
                    stek.pop();
                    stek.push(SKUP);
                    stek.push(PRINT);
                } else {
                    cerr << "Sintaksna greska! NAREDBA\n";
                    exit(EXIT_FAILURE);
                }
                break;

            /*
            LL(1) gramatika:                             Skupovi izbora:
            skup -> { lista_elemenata }                  {'{'}
            | BROJ .. BROJ                               {BROJ}
            | ID                                         {ID}
            */    
            case SKUP:
                if(preduvid==OZ){
                    stek.pop();
                    stek.push(ZZ);
                    stek.push(LISTA_ELEMENATA);
                    stek.push(OZ);
                } else if(preduvid==BROJ){
                    stek.pop();
                    stek.push(BROJ);
                    stek.push(TT);
                    stek.push(BROJ);
                } else if(preduvid==ID){
                    stek.pop();
                    stek.push(ID);
                } else {    
                    cerr << "Sintaksna greska! SKUP\n";
                    exit(EXIT_FAILURE);
                }
                break; 

            /*
            LL(1) gramatika:                             Skupovi izbora:
            lista_elemenata -> BROJ lista_elemenataP     {BROJ}
            */       
            case LISTA_ELEMENATA:
                if(preduvid==BROJ){
                    stek.pop();
                    stek.push(LISTA_ELEMENATAP);
                    stek.push(BROJ);
                } else {
                    cerr << "Sintaksna greska! LISTA_ELEMENATA\n";
                    exit(EXIT_FAILURE);
                }
                break;

            /*
            LL(1) gramatika:                             Skupovi izbora:
            lista_elemenataP -> , BROJ lista_elemenataP  {','}
            | eps                                        {'}'}
            */    
            case LISTA_ELEMENATAP:
                if(preduvid==ZAREZ){
                    stek.pop();
                    stek.push(LISTA_ELEMENATAP);
                    stek.push(BROJ);
                    stek.push(ZAREZ);
                } else if(preduvid==ZZ){
                    stek.pop();
                } else {
                    cerr << "Sintaksna greska! LISTA_ELEMENATAP\n";
                    exit(EXIT_FAILURE);
                }
                break;
            default:
                if(preduvid==stek.top()){
                    stek.pop();
                    preduvid=yylex();
                }
                break;                    
        }
    }

    cout << "Sve je u redu sa unetim skupovnim operacijama!\n";

    return 0;
}