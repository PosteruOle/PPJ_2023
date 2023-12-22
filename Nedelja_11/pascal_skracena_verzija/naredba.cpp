#include "naredba.hpp"
#include <map>

map<string, double> promenljive;

void Blok::izvrsi() const{
    for(Naredba *n: _naredbe){
        n->izvrsi();
    }
}

void IspisiS::izvrsi() const{
    string tmp;
    tmp=s.substr(1, s.size()-2);
    cout << tmp << endl;
}

void IspisiE::izvrsi() const{
    cout << izraz->izracunaj() << endl;
}

void Dodela::izvrsi() const{
    promenljive[s]=izraz->izracunaj();
}

void Unesi::izvrsi() const{
    double vrednost;
    cin >> vrednost;
    promenljive[_id]=vrednost;
}

void AkoJeOnda::izvrsi() const{ 
    if(_uslov->izracunaj()!=0)
        _naredba->izvrsi();
}

void AkoJeOndaInace::izvrsi() const{
    if(_uslov->izracunaj()!=0)
        _naredba1->izvrsi();
    else
        _naredba2->izvrsi();    
}

void DokJeRadiSledece::izvrsi() const{
    while(_uslov->izracunaj()){
        _blok->izvrsi();
    }
}