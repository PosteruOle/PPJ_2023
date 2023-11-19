#ifndef __SKUPOVI_HPP__
#define __SKUPOVI_HPP__

#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <set>

using namespace std;

class Skup{
    public:
    Skup(){ }

    Skup(set<int>& elementi){
        this->elementi=elementi;
    }
    
    Skup(Skup& s){
        this->elementi=s.getElementi();
    }

    int getSize();
    set<int> getElementi();
    void addElement(int x);
    void ispisi();
    Skup *unija(Skup *s);
    Skup *presek(Skup *s);
    Skup *razlika(Skup *s);
    Skup *komplement(Skup *universe);
    Skup *simetricna_razlika(Skup *s);
    bool checkElement(int x);
    bool checkSubset(Skup *s);
    
    private:
    set<int> elementi;
};



#endif