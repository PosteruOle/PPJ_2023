#ifndef __MATRICA_HPP__
#define __MATRICA_HPP__

#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>

using namespace std;

class Matrica{
public:
    Matrica(){ }

    Matrica(vector<vector<int>>& x){
        elements=x;
    }

    Matrica(Matrica *m){
        elements=m->getElements();
    }

    vector<vector<int>>& getElements(){
        return elements;
    }

    void ispisi();
    Matrica *saberi(Matrica *m);
    Matrica *oduzmi(Matrica *m);
    Matrica *pomnozi(Matrica *m);
    Matrica *pomnozi_pokoordinatno(Matrica *m);
    Matrica *transponuj();
    void addRow(vector<int>& v);
    int getBrojRedova();
    int getBrojKolona();
private:
    vector<vector<int>> elements;
};

#endif