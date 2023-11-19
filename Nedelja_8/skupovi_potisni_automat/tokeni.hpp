#ifndef __TOKENI_HPP__
#define __TOKENI_HPP__

/*
Naivna gramatika:
program -> naredba ';' program
| naredba ';'

naredba -> ID DODELA skup
| print skup

skup -> { lista_elemenata }
| BROJ .. BROJ 
| ID 

lista_elemenata -> BROJ , lista_elemenata
| BROJ

//--------------------------------------------

LL(1) gramatika:
program -> naredba ';' programP

programP -> naredba ';' programP
| eps

naredba -> ID DODELA skup
| print skup

skup -> { lista_elemenata }
| BROJ .. BROJ 
| ID 

lista_elemenata -> BROJ lista_elemenataP

lista_elemenataP -> , BROJ lista_elemenataP
| eps
*/

#define EOI 0
#define ID 1
#define BROJ 2
#define DODELA 3
#define TT 4
#define ZAREZ 5
#define OZ 6
#define ZZ 7
#define PRINT 8
#define TZ 9

#define PROGRAM 101
#define PROGRAMP 102
#define NAREDBA 103
#define SKUP 104
#define LISTA_ELEMENATA 105
#define LISTA_ELEMENATAP 106

#endif