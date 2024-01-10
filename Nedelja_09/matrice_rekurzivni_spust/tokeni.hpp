#ifndef __TOKENI_HPP__
#define __TOKENI_HPP__

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

#define EOI 0
#define BROJ 1
#define ID 2
#define TZ 3
#define OZ 4
#define ZZ 5
#define N 6
#define PRINTALL 7
#define DODELA 8

#endif