#ifndef __FUNKCIJE_HPP__
#define __ FUNKCIJE_HPP__

#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

//-------------------------------------------------
//Apstraktna klasa Izraz!
class Izraz{
public:
    virtual ~Izraz(){ }
    virtual bool proveri(const vector<char>& arg) const= 0;
    virtual void ispisi() const = 0;
    virtual double izracunaj() const = 0;
    virtual Izraz *izvod(char c) const = 0;
    virtual Izraz *kopija() const = 0;
};

class Konstanta : public Izraz{
public:
    Konstanta(){ }
    Konstanta(double vrednost){
        this->vrednost=vrednost;
    }
    ~Konstanta(){ }
    bool proveri(const vector<char>& arg) const;
    void ispisi() const;
    double izracunaj() const;
    Izraz *izvod(char c) const;
    Izraz *kopija() const;
private:
    double vrednost;    
}; 

class Promenljiva : public Izraz{
public:
    Promenljiva(){ }
    Promenljiva(char c){
        this->id=c;
    }
    ~Promenljiva(){ }
    bool proveri(const vector<char>& arg) const;
    void ispisi() const;
    double izracunaj() const;
    Izraz *izvod(char c) const;
    Izraz *kopija() const;
private:
    char id;    
};

//-------------------------------------------------
// Unarni izrazi!

class UnarniIzraz: public Izraz{
public:
    UnarniIzraz(){ }
    UnarniIzraz(Izraz *i){
        this->izraz=i;
    }
    ~UnarniIzraz(){
        delete izraz;
    }
    bool proveri(const vector<char>& arg) const;
protected:
    Izraz *izraz;
};

class Sinus: public UnarniIzraz{
public:
    Sinus(Izraz *izraz){
        this->izraz=izraz;
    }
    void ispisi() const;
    double izracunaj() const;
    Izraz *izvod(char c) const;
    Izraz *kopija() const;
};

class Kosinus: public UnarniIzraz{
public:
    Kosinus(Izraz * i){
        this->izraz=i;
    }
    void ispisi() const;
    double izracunaj() const;
    Izraz *izvod(char c) const;
    Izraz *kopija() const;
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
    bool proveri(const vector<char>& arg) const;
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
    void ispisi() const;
    double izracunaj() const;
    Izraz *izvod(char c) const;
    Izraz *kopija() const;
};

class Proizvod : public BinarniIzraz{
public:
    Proizvod(){ }
    Proizvod(Izraz *i1, Izraz* i2){
        this->izraz1=i1;
        this->izraz2=i2;
    }
    void ispisi() const;
    double izracunaj() const;
    Izraz *izvod(char c) const;
    Izraz *kopija() const;
};

//--------------------------------------------------------
// Klasa Funkcija!

class Funkcija{
public:
    Funkcija(){ }
    Funkcija(const vector<char>& argumenti, Izraz *izraz){
        this->argumenti=argumenti;
        this->izraz=izraz;
    }
    ~Funkcija(){
        delete izraz;
    }
    bool proveri() const;
    void ispisi() const;
    double izracunaj() const;
    Izraz *izvod(char c) const;
    double operator[](vector<double>& arg);

    vector<char> getArgumenti(){
        return argumenti;
    }
private:
    vector<char> argumenti;
    Izraz *izraz;
};

#endif