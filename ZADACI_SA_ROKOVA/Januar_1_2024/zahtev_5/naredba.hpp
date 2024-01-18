#ifndef __NAREDBA_HPP__
#define __NAREDBA_HPP__

#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <map>
#include "izrazi.hpp"

using namespace std;

class Naredba{
public:
    virtual void izvrsi() const = 0;
};

class Blok: public Naredba{
public:
    Blok(){ }
    Blok(vector<Naredba*> naredbe){
        _naredbe=naredbe;
    }
    void izvrsi() const;
    void addNaredba(Naredba *n){
        _naredbe.push_back(n);
    }
    vector<Naredba*> _naredbe;
};

class Print : public Naredba{
public:
    Print(){ }
    Print(string option, Izraz *izraz){
        _option=option;
        _izraz=izraz;
    }
    void izvrsi() const;
    string _option;
    Izraz *_izraz;
};

class Deklaracija: public Naredba{
public:
    Deklaracija(){ }
    Deklaracija(string id){
        _id=id;
    }
    void izvrsi() const;
    string _id;
};

class DeklaracijaSaInicijalizacijom: public Naredba{
public:
    DeklaracijaSaInicijalizacijom(){ }
    DeklaracijaSaInicijalizacijom(string id, Izraz *izraz){
        _id=id;
        _izraz=izraz;
    }
    void izvrsi() const;
    string _id;
    Izraz *_izraz;
};

class LogickaNaredba: public Naredba{
public:
    LogickaNaredba(){ }
    LogickaNaredba(string o, Izraz *i1, Izraz *i2){
        _operacija=o;
        _izraz1=i1;
        _izraz2=i2;
    }
    void izvrsi() const;
    string _operacija;
    Izraz *_izraz1;
    Izraz *_izraz2;    
};

#endif