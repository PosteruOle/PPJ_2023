#ifndef __NAREDBA_HPP__
#define __NAREDBA_HPP__

#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include "izrazi.hpp"

using namespace std;

class Naredba{
public:
    ~Naredba(){ }
    virtual void izvrsi() const = 0;
};

class Blok: public Naredba{
public:
    Blok(){ }
    Blok(vector<Naredba*>& naredbe){
        _naredbe=naredbe;
    }
    ~Blok(){
        for(Naredba *n: _naredbe){
            delete n;
        }
    }
    void izvrsi() const;
private:
    vector<Naredba*> _naredbe;
};

class IspisiS: public Naredba{
public:
    IspisiS(){ }
    IspisiS(string& s){
        this->s=s;
    }
    void izvrsi() const;
private:
    string s;
};

class IspisiE: public Naredba{
public:
    IspisiE(){ }
    IspisiE(Izraz * izraz){
        this->izraz=izraz;
    }
    ~IspisiE(){
        delete izraz;
    }
    void izvrsi() const;
private:
    Izraz *izraz;
};

class Dodela: public Naredba{
public:
    Dodela(){ }
    Dodela(string &s, Izraz * izraz){
        this->s=s;
        this->izraz=izraz;
    }
    ~Dodela(){
        delete izraz;
    }
    void izvrsi() const;
private:
    string s;
    Izraz *izraz;
};

class Unesi : public Naredba {
public:
    Unesi(){ }
    Unesi(const string& id){
        _id=id;
    }
    void izvrsi() const;
private:
    string _id;
};

class AkoJeOnda: public Naredba{
public:
    AkoJeOnda(){ }
    AkoJeOnda(Izraz *uslov, Naredba *naredba){
        _uslov=uslov;
        _naredba=naredba;
    }
    ~AkoJeOnda(){
        delete _uslov;
        delete _naredba;
    }
    void izvrsi() const;
private:
    Izraz *_uslov;
    Naredba *_naredba;
};

class AkoJeOndaInace: public Naredba{
public:
    AkoJeOndaInace(){ }
    AkoJeOndaInace(Izraz *uslov, Naredba *naredba1, Naredba *naredba2){
        _uslov=uslov;
        _naredba1=naredba1;
        _naredba2=naredba2;
    }
    ~AkoJeOndaInace(){
        delete _uslov;
        delete _naredba1;
        delete _naredba2;
    }
    void izvrsi() const;
private:
    Izraz *_uslov;
    Naredba *_naredba1;
    Naredba *_naredba2;
};

class DokJeRadiSledece: public Naredba{
public:
    DokJeRadiSledece(){ }
    DokJeRadiSledece(Izraz *uslov, Naredba* blok){
        _uslov=uslov;
        _blok=blok;
    }
    ~DokJeRadiSledece(){
        delete _uslov;
        delete _blok;
    }
    void izvrsi() const;
private:
    Izraz *_uslov;
    Naredba* _blok;
};

#endif