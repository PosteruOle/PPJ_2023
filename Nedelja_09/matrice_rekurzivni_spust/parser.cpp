#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <stack>
#include "tokeni.hpp"

using namespace std;

/*
Gramatika:                          Skupovi izbora:
program -> naredba '\n' programP    { PRINTALL, ID, [}

programP -> naredba '\n' programP   { PRINTALL, ID, [}
| eps                               { EOI}

naredba -> PRINTALL nastavak        { PRINTALL}
| ID DODELA matrica nastavak        { ID}
| matrica nastavak                  { [ }

nastavak -> ';'                     { ; }
| eps                               { \n }

matrica -> '[' niz_vrsta ']'        { [ }
| ID                                { ID }

niz_vrsta -> vrsta niz_vrstaP       { BROJ }

niz_vrstaP -> ';' vrsta niz_vrstaP  { ; }
| eps                               { ] }

vrsta -> BROJ vrstaP                { BROJ } 

vrstaP -> BROJ vrstaP               { BROJ }
| eps                               { ;  ]}
*/
void program();
void programP();
void naredba();
void nastavak();
void matrica();
void niz_vrsta();
void niz_vrstaP();
void vrsta();
void vrstaP();


extern int yylex();
int preduvid=0;

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
Gramatika:                          Skupovi izbora:
program -> naredba '\n' programP    { PRINTALL, ID, [}
*/
void program(){ 
    if(preduvid==PRINTALL || preduvid==ID || preduvid==OZ){
        //cout << "program -> naredba N programP\n";
        naredba();
        preduvid=yylex();
        programP();
    } else {
        cerr << "Sintaksna greska! PROGRAM\n";
        exit(EXIT_FAILURE);
    }
}

/*
Gramatika:                          Skupovi izbora:
programP -> naredba '\n' programP   { PRINTALL, ID, [}
| eps                               { EOI}
*/
void programP(){
    if(preduvid==PRINTALL || preduvid==ID || preduvid==OZ){
        //cout << "programP -> naredba N programP\n";
        naredba();
        preduvid=yylex();
        programP();
    } else if(preduvid==EOI){
        //cout << "programP -> eps\n";
        return;
    } else {
        cerr << "Sintaksna greska! PROGRAMP\n";
        exit(EXIT_FAILURE);
    }
}

/*
Gramatika:                          Skupovi izbora:
naredba -> PRINTALL nastavak        { PRINTALL}
| ID DODELA matrica nastavak        { ID}
| matrica nastavak                  { [ }
*/
void naredba(){
    if(preduvid==PRINTALL){
        //cout << "naredba -> PRINTALL nastavak\n";
        preduvid=yylex();
        nastavak();
    } else if(preduvid==ID){
        //cout << "naredba -> ID DODELA matrica nastavak\n";
        preduvid=yylex();
        preduvid=yylex();
        matrica();
        nastavak();
    } else if(preduvid==OZ){
        //cout << "naredba -> matrica nastavak\n";
        matrica();
        nastavak();
    } else {
        cerr << "Sintaksna greska! NAREDBA\n";
        exit(EXIT_FAILURE);
    }
}

/*
Gramatika:                          Skupovi izbora:
nastavak -> ';'                     { ; }
| eps                               { \n }
*/
void nastavak(){
    if(preduvid==TZ){
        //cout << "nastavak -> ';' \n";
        preduvid=yylex();
    } else if(preduvid==N){
        //cout << "nastavak -> eps\n";
        return;
    } else {
        cerr << "Sintaksna greska! NASTAVAK\n";
        exit(EXIT_FAILURE);
    }
}

/*
Gramatika:                          Skupovi izbora:
matrica -> '[' niz_vrsta ']'        { [ }
| ID                                { ID }
*/
void matrica(){
    if(preduvid==OZ){
        //cout << "matrica -> '[' niz_vrsta ']'" << endl;
        preduvid=yylex();
        niz_vrsta();
        if(preduvid!=ZZ){
            cerr << "Greska! Ocekivan token: ZZ\n";
            exit(EXIT_FAILURE);
        }
        preduvid=yylex();
    } else if(preduvid==ID){
        //cout << "matrica -> ID\n";
        preduvid=yylex();
    } else{
        cerr << "Sintaksna greska! MATRICA\n";
        exit(EXIT_FAILURE);
    }
}

/*
Gramatika:                          Skupovi izbora:
niz_vrsta -> vrsta niz_vrstaP       { BROJ }
*/
void niz_vrsta(){
    if(preduvid==BROJ){
        //cout << "niz_vrsta -> vrsta niz_vrstaP\n";
        vrsta();
        niz_vrstaP();
    } else {
        cerr << "Sintaksna greska! NIZ_VRSTA\n";
        exit(EXIT_FAILURE);
    }
}

/*
Gramatika:                          Skupovi izbora:
niz_vrstaP -> ';' vrsta niz_vrstaP  { ; }
| eps                               { ] }
*/
void niz_vrstaP(){
    if(preduvid==TZ){
        //cout << "niz_vrstaP -> ; vrsta niz_vrstaP\n";
        preduvid=yylex();
        vrsta();
        niz_vrstaP();
    } else if(preduvid==ZZ){
        //cout << "niz_vrstaP -> eps\n";
        return;
    }  else {
        cerr << "Sintaksna greska! NIZ_VRSTAP\n";
        exit(EXIT_FAILURE);
    }
}

/*
Gramatika:                          Skupovi izbora:
vrsta -> BROJ vrsta                 { BROJ } 
| eps                               { ; ]}
*/
void vrsta(){
    if(preduvid==BROJ){
        //cout << "vrsta -> BROJ vrsta\n";
        preduvid=yylex();
        vrsta();
    } else if(preduvid==TZ || preduvid==ZZ){
        //cout << "vrsta-> eps\n";
        return;
    } else {
        cerr << "Sintaksna greska! VRSTA\n";
        exit(EXIT_FAILURE);
    }
}

/*
Gramatika:                          Skupovi izbora:
vrstaP -> BROJ vrstaP               { BROJ }
| eps                               { ;  ]}
*/
void vrstaP(){
    if(preduvid==BROJ){
        //cout << "vrstaP -> BROJ vrstaP\n";
        preduvid=yylex();
        vrstaP();
    } else if(preduvid==TZ || preduvid==ZZ){
        //cout << "vrstaP -> eps\n";
        return;
    } else {
        cerr << "Sintaksna greska! VRSTAP\n";
        exit(EXIT_FAILURE);
    }
}