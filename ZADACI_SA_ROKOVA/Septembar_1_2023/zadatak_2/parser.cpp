/*
!!!LL(1) gramatika!!!
Gramtika:                                        Skupovi izbora:
program: naredba ';' program                     {BROJ_T, STAMPAJ}
| eps                                            {EOI}

naredba: BROJ ID nastavak                        {BROJ_T}
| STAMPAJ '(' lista_promenljivih ')'             {STAMPAJ}
 
nastavak: DODELA E                               {DODELA}
| eps                                            {';'}

lista_promenljivih: ID lista_promenljivihP       {ID}

lista_promenljivihP: ',' ID lista_promenljivihP  {','}
| eps                                            {')'}

izraz: SQRT '(' izraz ')'                        {SQRT}
| BROJ                                           {BROJ}
| ID                                             {ID}

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

int main(){




    return 0;
}