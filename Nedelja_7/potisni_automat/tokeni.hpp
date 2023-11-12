#ifndef __TOKENI_HPP__
#define __TOKENI_HPP__

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

#define EOI  (0)
#define BROJ (1)
#define PLUS (2)
#define PUTA (3)
#define OZ   (4)
#define ZZ   (5) 

#define E    (101)
#define EP   (102)
#define T    (103)
#define TP   (104)
#define F    (105)

#endif