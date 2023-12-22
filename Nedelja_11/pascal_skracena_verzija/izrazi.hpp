#ifndef __IZRAZI_HPP__
#define __IZRAZI_HPP__

#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <map>

using namespace std;

//-------------------------------------------------
//Apstraktna klasa Izraz!

class Izraz{
public:
    virtual ~Izraz(){ }
    virtual double izracunaj() const = 0;
    virtual Izraz *kopija() const = 0;
};

class Konstanta : public Izraz{
public:
    Konstanta(){ }
    Konstanta(double vrednost){
        this->vrednost=vrednost;
    }
    ~Konstanta(){ }
    double izracunaj() const;
    Izraz *kopija() const;
private:
    double vrednost;    
}; 

class Promenljiva : public Izraz{
public:
    Promenljiva(){ }
    Promenljiva(const string& s){
        this->id=s;
    }
    ~Promenljiva(){ }
    double izracunaj() const;
    Izraz *kopija() const;
private:
    string id;  
};

//-------------------------------------------------
// Binarni izrazi!

class BinarniIzraz : public Izraz{
public:
    BinarniIzraz(){ }
    BinarniIzraz(Izraz *i1, Izraz* i2){
        this->izraz1=i1;
        this->izraz2=i2;
    }
    ~BinarniIzraz(){
        delete izraz1;
        delete izraz2;
    }
protected:
    Izraz *izraz1;
    Izraz * izraz2;
};

class Zbir : public BinarniIzraz{
public:
    Zbir(){ }
    Zbir(Izraz *i1, Izraz* i2){
        this->izraz1=i1;
        this->izraz2=i2;
    }
    double izracunaj() const;
    Izraz *kopija() const;
};

class Razlika : public BinarniIzraz{
public:
    Razlika(){ }
    Razlika(Izraz *i1, Izraz* i2){
        this->izraz1=i1;
        this->izraz2=i2;
    }
    double izracunaj() const;
    Izraz *kopija() const;
};

class Proizvod : public BinarniIzraz{
public:
    Proizvod(){ }
    Proizvod(Izraz *i1, Izraz* i2){
        this->izraz1=i1;
        this->izraz2=i2;
    }
    double izracunaj() const;
    Izraz *kopija() const;
};

class Kolicnik : public BinarniIzraz{
public:
    Kolicnik(){ }
    Kolicnik(Izraz *i1, Izraz* i2){
        this->izraz1=i1;
        this->izraz2=i2;
    }
    double izracunaj() const;
    Izraz *kopija() const;
};

class Mod : public BinarniIzraz{
public:
    Mod(){ }
    Mod(Izraz *i1, Izraz* i2){
        this->izraz1=i1;
        this->izraz2=i2;
    }
    double izracunaj() const;
    Izraz *kopija() const;
};

// Za kraj ostavljamo klase koje ce predstavljati relacione operatore!

class Manje : public BinarniIzraz{
public:
    Manje(){ }
    Manje(Izraz *i1, Izraz* i2){
        this->izraz1=i1;
        this->izraz2=i2;
    }
    double izracunaj() const;
    Izraz *kopija() const;
};

class ManjeJednako : public BinarniIzraz{
public:
    ManjeJednako(){ }
    ManjeJednako(Izraz *i1, Izraz* i2){
        this->izraz1=i1;
        this->izraz2=i2;
    }
    double izracunaj() const;
    Izraz *kopija() const;
};

class Vece : public BinarniIzraz{
public:
    Vece(){ }
    Vece(Izraz *i1, Izraz* i2){
        this->izraz1=i1;
        this->izraz2=i2;
    }
    double izracunaj() const;
    Izraz *kopija() const;
};

class VeceJednako : public BinarniIzraz{
public:
    VeceJednako(){ }
    VeceJednako(Izraz *i1, Izraz* i2){
        this->izraz1=i1;
        this->izraz2=i2;
    }
    double izracunaj() const;
    Izraz *kopija() const;
};

class Jednako : public BinarniIzraz{
public:
    Jednako(){ }
    Jednako(Izraz *i1, Izraz* i2){
        this->izraz1=i1;
        this->izraz2=i2;
    }
    double izracunaj() const;
    Izraz *kopija() const;
};

class Razlicito: public BinarniIzraz{
public:
    Razlicito(){ }
    Razlicito(Izraz *i1, Izraz* i2){
        this->izraz1=i1;
        this->izraz2=i2;
    }
    double izracunaj() const;
    Izraz *kopija() const;
};

#endif