#ifndef __IZRAZI_HPP__
#define __IZRAZI_HPP__

#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <map>

using namespace std;

class Izraz{
public:
    virtual int vrednost() const = 0;
};

class Promenljiva: public Izraz{
public:
    Promenljiva(){ }
    Promenljiva(string& id){
        _id=id;
    }
    int vrednost() const;
    string _id;    
};

class Konstanta: public Izraz{
public:
    Konstanta(){ }
    Konstanta(int x){
        _x=x;
    }
    int vrednost() const;
    int _x;
};

class UnarniIzraz: public Izraz{
public:
    UnarniIzraz(){ }
    UnarniIzraz(string o, Izraz *izraz){
        _operacija=o;
        _izraz=izraz;
    }
    int vrednost() const;
    string _operacija;
    Izraz *_izraz;
};

class BinarniIzraz: public Izraz{
public:
    BinarniIzraz(){ }
    BinarniIzraz(string o, Izraz *i1, Izraz *i2){
        _operacija=o;
        _izraz1=i1;
        _izraz2=i2;
    }
    int vrednost() const;
    string _operacija;
    Izraz *_izraz1;
    Izraz *_izraz2;
};

#endif