#include "izrazi.hpp"
#include <cmath>

extern map<string, double> promenljive;

//-----------------------------------------------
// Konstanta!

double Konstanta::izracunaj() const{
    return vrednost;
}

Izraz *Konstanta::kopija() const{
    return new Konstanta(vrednost);
}

//-----------------------------------------------
// Promenljiva!

double Promenljiva::izracunaj() const{
    if(promenljive.find(id)==promenljive.end()){
        cerr << "Promenljiva nije definisana!\n";
        exit(EXIT_FAILURE);
    }
    return promenljive[id];
}

Izraz *Promenljiva::kopija() const{
    return new Promenljiva(id);
}

//-----------------------------------------------
// Binarni izraz!

double Zbir::izracunaj() const{
    return izraz1->izracunaj() + izraz2->izracunaj();
}

Izraz *Zbir::kopija() const{
    return new Zbir(izraz1->kopija(), izraz2->kopija());
}

double Razlika::izracunaj() const{
    return izraz1->izracunaj() - izraz2->izracunaj();
}

Izraz *Razlika::kopija() const{
    return new Razlika(izraz1->kopija(), izraz2->kopija());
}

double Proizvod::izracunaj() const{
    return izraz1->izracunaj() * izraz2->izracunaj();
}

Izraz *Proizvod::kopija() const{
    return new Proizvod(izraz1->kopija(), izraz2->kopija());
}

double Mod::izracunaj() const{
    return int(izraz1->izracunaj()) % int(izraz2->izracunaj());
}

Izraz *Mod::kopija() const{
    return new Mod(izraz1->kopija(), izraz2->kopija());
}

double Kolicnik::izracunaj() const{
    return izraz1->izracunaj() / izraz2->izracunaj();
}

Izraz *Kolicnik::kopija() const{
    return new Kolicnik(izraz1->kopija(), izraz2->kopija());
}

// Za kraj ostavljamo implementacije svih metoda onih klasa kojima predstavljamo relacione operatore!
// Implementacija metoda za klasu Manje!

double Manje::izracunaj() const{ 
    return izraz1->izracunaj() < izraz2->izracunaj();
}

Izraz *Manje::kopija() const{
    return new Manje(izraz1->kopija(), izraz2->kopija());
}

// Implementacija metoda za klasu ManjeJednako!

double ManjeJednako::izracunaj() const{ 
    return izraz1->izracunaj() <= izraz2->izracunaj();
}

Izraz *ManjeJednako::kopija() const{
    return new Manje(izraz1->kopija(), izraz2->kopija());
}

// Implementacija metoda za klasu Vece!

double Vece::izracunaj() const{ 
    return izraz1->izracunaj() > izraz2->izracunaj();
}

Izraz *Vece::kopija() const{
    return new Vece(izraz1->kopija(), izraz2->kopija());
}

// Implementacija metoda za klasu VeceJednako!

double VeceJednako::izracunaj() const{ 
    return izraz1->izracunaj() >= izraz2->izracunaj();
}

Izraz *VeceJednako::kopija() const{
    return new VeceJednako(izraz1->kopija(), izraz2->kopija());
}

// Implementacija metoda za klasu Jednako!

double Jednako::izracunaj() const{ 
    return izraz1->izracunaj() == izraz2->izracunaj();
}

Izraz *Jednako::kopija() const{
    return new Jednako(izraz1->kopija(), izraz2->kopija());
}

// Implementacija metoda za klasu Razlicito!

double Razlicito::izracunaj() const{ 
    return izraz1->izracunaj() != izraz2->izracunaj();
}

Izraz *Razlicito::kopija() const{
    return new Razlicito(izraz1->kopija(), izraz2->kopija());
}