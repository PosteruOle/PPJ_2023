#ifndef __TOKENI_HPP__
#define __TOKENI_HPP__

/* Gramatika:                                           Skupovi izbora
 * niz_deklaracija -> deklaracija TZ niz_deklaracija     { EL_TIP, ID}
 *   | eps                                               { EOI }
 *  deklaracija -> tip niz_promenljivih TZ               { EL_TIP, ID }
 *  tip -> EL_TIP tip_prim                               { EL_TIP }
 *  | ID tip_prim                                        { ID }
 *  tip_prim -> OZ ZZ tip_prim                           { OZ }
 *            | eps                                      { ID }
 *  niz_promenljivih -> ID niz_promenljvih_prim          { ID }
 *  niz_promenljivih_prim -> Z ID niz_promenljivih_prim  { Z }
 *  | eps                                                { TZ }                                                 
 */

#define EOI    (0)
#define EL_TIP (1)
#define ID     (2)
#define Z      (3)
#define OZ     (4)
#define ZZ     (5)
#define TZ     (6) 

#define niz_deklaracija        (101)
#define deklaracija            (102)
#define tip                    (103)
#define tip_prim               (104)
#define niz_promenljivih       (105)
#define niz_promenljivih_prim  (106)

#endif