#include "naredba.hpp"

map<string, int> promenljive;

void Print::izvrsi() const{
    if(_option=="%b"){
        //printf("0b%d\n", _izraz->vrednost());
        unsigned mask=1<<(sizeof(int)*8-1);
        int vrednost=_izraz->vrednost();
        bool flag=true;
        for(int i=1;i<=sizeof(int)*8;i++){
            if((mask & vrednost)!=0){
                flag=false;
                cout << "1";
            } else {
                cout << "0";
            }    
            mask>>=1;
        }
        cout << endl;
    } else if(_option=="%d"){
        printf("%d\n", _izraz->vrednost());
    } else if(_option=="%h"){
        printf("%x\n", _izraz->vrednost());
    }
}

void Blok::izvrsi() const{
    for(Naredba *n: _naredbe){
        n->izvrsi();
    }
}

void Deklaracija::izvrsi() const{
    promenljive[_id]=0;
}

void LogickaNaredba::izvrsi() const{
    if(_operacija=="=="){
        if(_izraz1->vrednost()==_izraz2->vrednost())
            cout << "True!\n";
        else
            cout << "False!\n";    
    } else if(_operacija=="!="){
        if(_izraz1->vrednost()!=_izraz2->vrednost())
            cout << "True!\n";
        else
            cout << "False!\n";
    }
}

void DeklaracijaSaInicijalizacijom::izvrsi() const{
    promenljive[_id]=_izraz->vrednost();
}