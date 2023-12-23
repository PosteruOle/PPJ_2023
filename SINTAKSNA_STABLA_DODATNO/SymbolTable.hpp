#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <iostream>
#include <cstdlib>
#include <map>
#include <exception>

/* klasa predstavlja tablicu simbola 
 * U slucaju da program podrzava vise tipova podataka, definisali bismo
 * odvojenu tablicu za svaki tip. Nas program podrzava samo realne brojeve
 * i zbog toga nam treba samo jedan tablica. U opstem slucaju, klasa bi trebalo
 * da bude sablon. 
 */
class SymbolTable {

private:
    /* kao atribut cuvamo mapu u kojoj je kljuc naziv promenljive 
     * a vrednost je realan broj. 
     */
    std::map<std::string, double> _symbols;
public:
    /* konstruktor */
    SymbolTable();

    /* javni interfejs klase */
    bool SymbolDefined(const std::string& s) const;
    double GetSymbolValue(const std::string& s) const;
    bool SetSymbolValue(const std::string& s, double val);
};

#endif
