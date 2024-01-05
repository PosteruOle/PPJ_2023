/*
!!!LL(1) GRAMATIKA!!!
Gramatika:                              Skupovi izbora: 
program: naredba ';' programP           {LIST, ID}

programP: naredba ';' programP          {LIST, ID}
| eps                                   {EOI}

naredba: LIST '<' tip '>' ID nastavak1  {LIST}
| ID nastavak2                          {ID}

tip: NUMBER                             {NUMBER} 
| STRING                                {STRING}

nastavak1: '=' '{' lista '}'            {'='}
| eps                                   {';'}

nastavak2: '=' ID                       {'='}
| '.' nastavak3                         {'.'}

nastavak3: PRINT '(' ')'                {PRINT}
| PRINT_R '(' ')'                       {PRINT_R}

lista: lista_brojeva                    {BROJ}
| lista_stringova                       {REAL_STRING}


lista_brojeva: BROJ lista_brojevaP      {BROJ}

lista_brojevaP: ',' BROJ lista_brojevaP {,}
| eps                                   {'}'}

lista_stringova: REAL_STRING lista_stringovaP      {REAL_STRING}

lista_stringovaP: ',' REAL_STRING lista_stringovaP {','}
| eps                                              {'}'}

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
void tip();
void nastavak1();
void nastavak2();
void nastavak3();
void lista();
void lista_brojeva();
void lista_brojevaP();
void lista_stringova();
void lista_stringovaP();

int main(){

    preduvid=yylex();
    program();
    if(preduvid!=EOI){
        cerr << "Sintaksna greska! Visak tokena na ulazu!\n";
        exit(EXIT_FAILURE);
    } else {
        cout << "Sve je u redu sa unetim naredbama!\n";
    }

    return 0;
}

void program(){ 
    if(preduvid==LIST || preduvid==ID){
        naredba();
        if(preduvid!=';'){
            cerr << "Sintaksna greska! PROGRAM\n";
            exit(EXIT_FAILURE);
        }
        preduvid=yylex();
        programP();
    } else {
        cerr << "Sintaksna greska! PROGRAM\n";
        exit(EXIT_FAILURE);
    }
}

void programP(){
    if(preduvid==LIST || preduvid==ID){
        naredba();
        if(preduvid!=';'){
            cerr << "Sintaksna greska! PROGRAM\n";
            exit(EXIT_FAILURE);
        }
        preduvid=yylex();
        programP();
    } else if(preduvid==EOI){
        return;
    } else {
        cerr << "Sintaksna greska! PROGRAM\n";
        exit(EXIT_FAILURE);
    }
}

void naredba(){
    if(preduvid==LIST){
        preduvid=yylex();
        preduvid=yylex();
        tip();
        preduvid=yylex();
        preduvid=yylex();
        nastavak1();
    } else if(preduvid==ID){
        preduvid=yylex();
        nastavak2();
    } else {
        cerr << "Sintaksna greska! NAREDBA\n";
        exit(EXIT_FAILURE);
    }
}

void tip(){
    if(preduvid==NUMBER){
        preduvid=yylex();
    } else if(preduvid==STRING){
        preduvid=yylex();
    } else {
        cerr << "Sintaksna greska! TIP\n";
        exit(EXIT_FAILURE);
    }
}

void nastavak1(){
    if(preduvid=='='){
        preduvid=yylex();
        preduvid=yylex();
        lista();
        preduvid=yylex();
    } else if(preduvid==';'){
        return;
    } else {
        cerr << "Sintaksna greska! NASTAVAK1\n";
        exit(EXIT_FAILURE);
    }
}

void nastavak2(){
    if(preduvid=='='){
        preduvid=yylex();
        preduvid=yylex();
    } else if(preduvid=='.'){
        preduvid=yylex();
        nastavak3();
    } else {
        cerr << "Sintaksna greska! NASTAVAK2\n";
        exit(EXIT_FAILURE);
    }
}

void nastavak3(){
    if(preduvid==PRINT){
        preduvid=yylex();
        preduvid=yylex();
        preduvid=yylex();
    } else if(preduvid==PRINT_R){
        preduvid=yylex();
        preduvid=yylex();
        preduvid=yylex();
    } else {
        cerr << "Sintaksna greska! NASTAVAK3\n";
        exit(EXIT_FAILURE);
    }
}

void lista(){
    if(preduvid==BROJ){
        lista_brojeva();
    } else if(preduvid==REAL_STRING){
        lista_stringova();
    } else {
        cerr << "Sintaksna greska! LISTA\n";
        exit(EXIT_FAILURE);
    }
}

void lista_brojeva(){
    if(preduvid==BROJ){
        preduvid=yylex();
        lista_brojevaP();
    } else {
        cerr << "Sintaksna greska! LISTA_BROJEVA\n";
        exit(EXIT_FAILURE);
    }
}

void lista_brojevaP(){
    if(preduvid==','){
        preduvid=yylex();
        preduvid=yylex();
        lista_brojevaP();
    } else if(preduvid=='}'){
        return;
    } else {
        cerr << "Sintaksna greska! LISTA_BROJEVAP\n";
        exit(EXIT_FAILURE);
    }
}

void lista_stringova(){
    if(preduvid==REAL_STRING){
        preduvid=yylex();
        lista_brojevaP();
    } else {
        cerr << "Sintaksna greska! LISTA_STRINGOVA\n";
        exit(EXIT_FAILURE);
    }
}

void lista_stringovaP(){
    if(preduvid==','){
        preduvid=yylex();
        preduvid=yylex();
        lista_brojevaP();
    } else if(preduvid=='}'){
        return;
    } else {
        cerr << "Sintaksna greska! LISTA_STRINGOVAP\n";
        exit(EXIT_FAILURE);
    }
}