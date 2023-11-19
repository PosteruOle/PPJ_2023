#include "skupovi.hpp"

set<int> Skup::getElementi(){
    return elementi;
}

int Skup::getSize(){
    return elementi.size();
}

void Skup::addElement(int x){
    elementi.insert(x);
}

void Skup::ispisi(){
    if(elementi.size()==0){
        cout << "{ }\n";
        return;
    }
    cout << "{";
    for(auto it=elementi.begin();it!=elementi.end();it++){
        if(it==(--elementi.end())){
            cout << *it << "}\n";
            return;
        }
        cout << *it << ", ";
    }
}

Skup *Skup::unija(Skup *s){
    set<int> set=s->getElementi();
    for(auto it=set.begin();it!=set.end();it++){
        elementi.insert(*it);
    }
    return new Skup(elementi);
}

Skup *Skup::presek(Skup *s){
    set<int> result;
    set<int> set=s->getElementi();
    for(auto it=set.begin();it!=set.end();it++){
        if(elementi.find(*it)!=elementi.end()){
            result.insert(*it);
        }
    }
    return new Skup(result);
}
    
Skup *Skup::razlika(Skup *s){
    set<int> result;
    set<int> set=s->getElementi();
    for(auto it=elementi.begin();it!=elementi.end();it++){
        if(set.find(*it)==set.end()){
            result.insert(*it);
        }
    }
    return new Skup(result);
}

Skup *Skup::simetricna_razlika(Skup *s){
    //TODO!
    set<int> result;
    set<int> set=s->getElementi();
    for(auto it=elementi.begin();it!=elementi.end();it++){
        if(set.find(*it)==set.end()){
            result.insert(*it);
        }
    }
    return new Skup(result);
}

bool Skup::checkElement(int x){
    for(auto it=elementi.begin();it!=elementi.end();it++){
        if(*it==x)
            return true;
    }
    return false;
}

bool Skup::checkSubset(Skup *s){
    return false;
}

Skup *Skup::komplement(Skup *universe){
    set<int> result;
    set<int> universal_set=universe->getElementi();
    if(elementi.size()>universal_set.size()){
        cerr << "Prosledjeni skup je veci od univerzalnog skupa!\n";
        exit(EXIT_FAILURE);
    }

    for(auto it=elementi.begin();it!=elementi.end();it++){
        if(universal_set.find(*it)==universal_set.end()){
            cerr << "Prosledjeni skup sadrzi elemnt koji ne pripada univerzalnom skupu!\n";
            exit(EXIT_FAILURE);
        }
    }

    for(auto it=universal_set.begin();it!=universal_set.end();it++){
        if(elementi.find(*it)==elementi.end()){
            result.insert(*it);
        }
    }

    return new Skup(result);
}