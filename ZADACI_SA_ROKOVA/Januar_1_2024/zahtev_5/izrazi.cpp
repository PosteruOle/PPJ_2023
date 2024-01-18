#include "izrazi.hpp"

extern map<string, int> promenljive;

int Promenljiva::vrednost() const{
    if(promenljive.find(_id)==promenljive.end()){
        cerr << "Promenljiva nije definisana!\n";
        return 0;
    }
    return promenljive[_id];
}

int Konstanta::vrednost() const{
    return _x;
}

int UnarniIzraz::vrednost() const{
    if(_operacija=="~"){
        return ~_izraz->vrednost();
    } else if(_operacija=="-"){
        return -_izraz->vrednost();
    }
    return -100000;
}

int BinarniIzraz::vrednost() const{
    if(_operacija=="+"){
        return _izraz1->vrednost()+_izraz2->vrednost();
    } else if(_operacija=="-"){
        return _izraz1->vrednost()-_izraz2->vrednost();
    } else if(_operacija=="*"){
        return _izraz1->vrednost()*_izraz2->vrednost();
    } else if(_operacija=="/"){
        return _izraz1->vrednost()/_izraz2->vrednost();
    } else if(_operacija=="%"){
        return _izraz1->vrednost()%_izraz2->vrednost();
    } else if(_operacija=="&"){
        return _izraz1->vrednost()&_izraz2->vrednost();
    } else if(_operacija=="|"){
        return _izraz1->vrednost()|_izraz2->vrednost();
    } else if(_operacija=="^"){
        return _izraz1->vrednost()^_izraz2->vrednost();
    } else if(_operacija=="<<"){
        return _izraz1->vrednost()<<_izraz2->vrednost();
    } else if(_operacija==">>"){
        return _izraz1->vrednost()>>_izraz2->vrednost();
    } else if(_operacija=="=="){
        return _izraz1->vrednost()==_izraz2->vrednost();
    } else if(_operacija=="!="){
        return _izraz1->vrednost()!=_izraz2->vrednost();
    }
    return -100000;
}