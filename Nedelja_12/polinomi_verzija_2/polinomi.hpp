#ifndef __POLINOMI_HPP__
#define __POLINOMI_HPP__

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

class Polinom{
public:
    Polinom(){ }
    
    Polinom(vector<double>& koeficijenti){
        _koeficijenti=koeficijenti;
    }
    
    Polinom(Polinom& p){
        _koeficijenti=p.getKoeficijenti();
    }

    vector<double> getKoeficijenti(){
        return _koeficijenti;
    }

    void ispisi() const;
    bool jednako(Polinom *p) const;
    bool razlicito(Polinom *p) const;
    Polinom *negiraj() const;
    Polinom *saberi(Polinom* p) const;
    Polinom *oduzmi(Polinom* p) const;
    Polinom *pomnozi(Polinom* p) const;
    Polinom *izvod() const;
    Polinom *integral(double x) const;
    double operator[](double x) const;
    double vrednost(double x) const;
private:
    vector<double> _koeficijenti;
};

#endif