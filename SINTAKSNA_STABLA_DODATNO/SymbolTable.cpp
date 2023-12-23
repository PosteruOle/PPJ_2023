#include "SymbolTable.hpp"

SymbolTable::SymbolTable() : _symbols(){

}

/* metod proverava da li u tablici simbola postoji promenljvia sa datim imenom */
bool SymbolTable::SymbolDefined(const std::string& s) const {

    return _symbols.find(s) != _symbols.end();
}
/* metod vraca vrednost pridruzenu promenljivoj */
double SymbolTable::GetSymbolValue(const std::string& s) const {
    
    /* ako promenljiva ne postoji bacamo izuzetak */
    if (!SymbolDefined(s))
        throw std::invalid_argument("Variable not defined");

    /* ako postoji, vracamo njenu vrednost */
    return _symbols.find(s)->second;
}
/* ako promenljiva postoji, menjamo njenu vrednost. ako ne postoji, 
 * upisujemo je u tablicu. 
 */
bool SymbolTable::SetSymbolValue(const std::string& s, double val) {
    
    _symbols[s] = val;
    return true;
}