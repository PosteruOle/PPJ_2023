/*
Gramatika:                              Skupovi izbora:
program: naredba ';' programP           {STACK, ID, PRINT_STACK}
 
programP: naredba ';' programP          {STACK, ID, PRINT_STACK}
| eps                                   {EOI}

naredba: STACK '<' INT '>' ID nastavak  {STACK}
| ID DODELA ID                          {ID}
| PRINT_STACK '(' ID ')'                {PRINT_STACK}

nastavak: DODELA nastavak1              {DODELA}                                    
| eps                                   {';'}

nastavak1: '{' lista '}'                {'{'}
| ID                                    {ID}

lista: BROJ listaP                      {BROJ}
 
listaP: ',' BROJ listaP                 {','}
| eps                                   {'}'}
*/
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <stack>
#include "tokeni.hpp"

using namespace std;

extern int yylex();

int preduvid=0;

void program();
void programP();
void naredba();
void nastavak();
void nastavak1();
void lista();
void listaP();

int main(){

    preduvid=yylex();
    program();

    if(preduvid==EOI){
        cout << "Sve je u redu sa unetim naredbama!\n";
    } else {
        cerr << "Sintaksna greska! Visak tokena na ulazu!\n";
        exit(EXIT_FAILURE);
    }

    return 0;
}

/*
Gramatika:                              Skupovi izbora:
program: naredba ';' programP           {STACK, ID, PRINT_STACK}
*/
void program(){
    if(preduvid==STACK || preduvid==ID || preduvid==PRINT_STACK){
        naredba();
        preduvid=yylex();
        programP();
    } else {
        cerr << "Sintaksna greska! PROGRAM\n";
        exit(EXIT_FAILURE);
    }
}

/*
Gramatika:                              Skupovi izbora:
programP: naredba ';' programP          {STACK, ID, PRINT_STACK}
| eps                                   {EOI}
*/
void programP(){
    if(preduvid==STACK || preduvid==ID || preduvid==PRINT_STACK){
        naredba();
        preduvid=yylex();
        programP();
    } else if(preduvid==EOI){
        return;
    } else {
        cerr << "Sintaksna greska! PROGRAMP\n";
        exit(EXIT_FAILURE);
    }
}

/*
Gramatika:                              Skupovi izbora:
naredba: STACK '<' INT '>' ID nastavak  {STACK}
| ID DODELA ID                          {ID}
| PRINT_STACK '(' ID ')'                {PRINT_STACK}
*/
void naredba(){
    if(preduvid==STACK){
        preduvid=yylex();
        preduvid=yylex();
        preduvid=yylex();
        preduvid=yylex();
        preduvid=yylex();
        nastavak();
    } else if(preduvid==ID){
        preduvid=yylex();
        preduvid=yylex();
        preduvid=yylex();
    } else if(preduvid==PRINT_STACK){
        preduvid=yylex();
        preduvid=yylex();
        preduvid=yylex();
        preduvid=yylex();
    } else {
        cerr << "Sintaksna greska! NAREDBA\n";
        exit(EXIT_FAILURE);
    }
}

/*
Gramatika:                              Skupovi izbora:
nastavak: DODELA '{' lista '}'          {DODELA}
| eps                                   {';'}
*/
void nastavak(){
    if(preduvid==DODELA){
        preduvid=yylex();
        nastavak1();
    } else if(preduvid==';'){
        return;
    } else {
        cerr << "Sintaksna greska! NASTAVAK\n";
        exit(EXIT_FAILURE);
    }
}

/*
Gramatika:                              Skupovi izbora:
nastavak1: '{' lista '}'                {'{'}
| ID                                    {ID}
*/
void nastavak1(){
    if(preduvid=='{'){
        preduvid=yylex();
        lista();
        preduvid=yylex();
    } else if(preduvid==ID){
        preduvid=yylex();
    } else {
        cerr << "Sintaksna greska! NASTAVAK1\n";
        exit(EXIT_FAILURE);
    }
}

/*
Gramatika:                              Skupovi izbora:
lista: BROJ listaP                      {BROJ}
*/
void lista(){
    if(preduvid==BROJ){
        preduvid=yylex();
        listaP();
    } else {
        cerr << "Sintaksna greska! LISTA\n" << preduvid << endl;
        exit(EXIT_FAILURE);
    }
}

/*
Gramatika:                              Skupovi izbora:
listaP: ',' BROJ listaP                 {','}
| eps                                   {'}'}
*/
void listaP(){
    if(preduvid==','){
        preduvid=yylex();
        preduvid=yylex();
        listaP();
    } else if(preduvid=='}'){
        return;
    } else {
        cerr << "Sintaksna greska! LISTAP\n";
        exit(EXIT_FAILURE);
    }
}