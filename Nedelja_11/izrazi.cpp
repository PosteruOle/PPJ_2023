#include "izrazi.hpp"
#include <cmath>

extern map<string, double> promenljive;

//-----------------------------------------------
// Konstanta!

bool Konstanta::proveri(const vector<char>& arg) const{
    return true;
}
void Konstanta::ispisi() const{
    cout << vrednost;
}

double Konstanta::izracunaj() const{
    return vrednost;
}

Izraz *Konstanta::izvod(char c) const{
    return new Konstanta(0);
}

Izraz *Konstanta::kopija() const{
    return new Konstanta(vrednost);
}

//-----------------------------------------------
// Promenljiva!

bool Promenljiva::proveri(const vector<char>& arg) const{
    /*
    for(string& c: arg){
        if(c==id)
            return true;
    }
    */
    return true;
}
void Promenljiva::ispisi() const{
    cout << id;
}

double Promenljiva::izracunaj() const{
    if(promenljive.find(id)==promenljive.end()){
        cerr << "Promenljiva nije definisana!\n";
        exit(EXIT_FAILURE);
    }
    return promenljive[id];
}

Izraz *Promenljiva::izvod(char c) const{
    if(c==id[0]){
        return new Konstanta(1);
    } else {
        return new Konstanta(0);
    }
}

Izraz *Promenljiva::kopija() const{
    return new Promenljiva(id);
}

//-----------------------------------------------
// Binarni izraz!

bool BinarniIzraz::proveri(const vector<char>& arg) const{
    return izraz1->proveri(arg) && izraz2->proveri(arg);
}

void Zbir::ispisi() const{
    cout << "(";
    izraz1->ispisi();
    cout << ") + (";
    izraz2->ispisi();
    cout << ")";
}

double Zbir::izracunaj() const{
    return izraz1->izracunaj() + izraz2->izracunaj();
}

Izraz *Zbir::izvod(char c) const{
    return new Zbir(izraz1->izvod(c), izraz2->izvod(c)); 
}

Izraz *Zbir::kopija() const{
    return new Zbir(izraz1->kopija(), izraz2->kopija());
}

void Razlika::ispisi() const{
    cout << "(";
    izraz1->ispisi();
    cout << ") - (";
    izraz2->ispisi();
    cout << ")";
}

double Razlika::izracunaj() const{
    return izraz1->izracunaj() - izraz2->izracunaj();
}

Izraz *Razlika::izvod(char c) const{
    return new Razlika(izraz1->izvod(c), izraz2->izvod(c)); 
}

Izraz *Razlika::kopija() const{
    return new Razlika(izraz1->kopija(), izraz2->kopija());
}

void Proizvod::ispisi() const{
    cout << "(";
    izraz1->ispisi();
    cout << ") * (";
    izraz2->ispisi();
    cout << ")";
}

double Proizvod::izracunaj() const{
    return izraz1->izracunaj() * izraz2->izracunaj();
}

Izraz *Proizvod::izvod(char c) const{
    return new Zbir(new Proizvod(izraz1->kopija()->izvod(c), izraz2->kopija()), new Proizvod(izraz1->kopija(), izraz2->kopija()->izvod(c))); 
}

Izraz *Proizvod::kopija() const{
    return new Proizvod(izraz1->kopija(), izraz2->kopija());
}

void Mod::ispisi() const{ 
    cout << "(";
    izraz1->ispisi();
    cout << ") mod (";
    izraz2->ispisi();
    cout << ")";
}

double Mod::izracunaj() const{
    return int(izraz1->izracunaj()) % int(izraz2->izracunaj());
}

Izraz *Mod::izvod(char c) const{
    return new Zbir(new Mod(izraz1->kopija()->izvod(c), izraz2->kopija()), new Mod(izraz1->kopija(), izraz2->kopija()->izvod(c)));
}

Izraz *Mod::kopija() const{
    return new Mod(izraz1->kopija(), izraz2->kopija());
}

void Kolicnik::ispisi() const{ 
    cout << "(";
    izraz1->ispisi();
    cout << ") / (";
    izraz2->ispisi();
    cout << ")";
}

double Kolicnik::izracunaj() const{
    return izraz1->izracunaj() / izraz2->izracunaj();
}

Izraz *Kolicnik::izvod(char c) const{
    // Podsetnik kako izgleda izvod kolicnika!
    // (a/b)'=(a'b-ab')/b^2
    return new Zbir(new Razlika(new Proizvod(izraz1->izvod(c), izraz2->kopija()), new Proizvod(izraz1->kopija(), izraz2->izvod(c))), new Proizvod(izraz2->kopija(), izraz2->kopija()));
}

Izraz *Kolicnik::kopija() const{
    return new Kolicnik(izraz1->kopija(), izraz2->kopija());
}

//-----------------------------------------------
// Unarni izraz!

bool UnarniIzraz::proveri(const vector<char>& arg) const{
    return izraz->proveri(arg);
}

void Sinus::ispisi() const{ 
    cout << "sin(";
    izraz->ispisi();
    cout << ")";
}

double Sinus::izracunaj() const{ 
    return sin(izraz->izracunaj());
}

Izraz *Sinus::izvod(char c) const{ 
    //TODO!
    //return new Kosinus(izraz);
    return new Proizvod(new Kosinus(izraz), izraz->kopija()->izvod(c));
}

Izraz *Sinus::kopija() const{ 
    return new Sinus(izraz->kopija());
}

void Kosinus::ispisi() const{ 
    cout << "cos(";
    izraz->ispisi();
    cout << ")";
}

double Kosinus::izracunaj() const{ 
    return cos(izraz->izracunaj());
}

Izraz *Kosinus::izvod(char c) const{ 
    //TODO!
    //Prvi pokusaj( dok jos uvek nije postojala klasa Prozivod)!
    //return new Sinus(izraz);
    
    //Drugi pokusaj!
    //return new Proizvod(new Sinus(izraz), izraz->kopija()->izvod(c));
    
    //Tacno resenje!
    return new Proizvod(new Konstanta(-1),new Proizvod(new Sinus(izraz), izraz->kopija()->izvod(c)));
}

Izraz *Kosinus::kopija() const{ 
    return new Kosinus(izraz);
}

// Za kraj ostavljamo implementacije svih metoda onih klasa kojima predstavljamo relacione operatore!
// Implementacija metoda za klasu Manje! 

void Manje::ispisi() const{
    cout << "(";
    izraz1->ispisi();
    cout << ") < (";
    izraz2->ispisi();
    cout << ")";
}

Izraz *Manje::izvod(char c) const{
    //Ovu funkciju necemo koristiti!
    return new Manje();
}

double Manje::izracunaj() const{ 
    return izraz1->izracunaj() < izraz2->izracunaj();
}

Izraz *Manje::kopija() const{
    return new Manje(izraz1->kopija(), izraz2->kopija());
}

// Implementacija metoda za klasu ManjeJednako!

void ManjeJednako::ispisi() const{
    cout << "(";
    izraz1->ispisi();
    cout << ") <= (";
    izraz2->ispisi();
    cout << ")";
}

Izraz *ManjeJednako::izvod(char c) const{
    //Ovu funkciju necemo koristiti!
    return new ManjeJednako();
}

double ManjeJednako::izracunaj() const{ 
    return izraz1->izracunaj() <= izraz2->izracunaj();
}

Izraz *ManjeJednako::kopija() const{
    return new Manje(izraz1->kopija(), izraz2->kopija());
}

// Implementacija metoda za klasu Vece!

void Vece::ispisi() const{
    cout << "(";
    izraz1->ispisi();
    cout << ") > (";
    izraz2->ispisi();
    cout << ")";
}

Izraz *Vece::izvod(char c) const{
    //Ovu funkciju necemo koristiti!
    return new Vece();
}

double Vece::izracunaj() const{ 
    return izraz1->izracunaj() > izraz2->izracunaj();
}

Izraz *Vece::kopija() const{
    return new Vece(izraz1->kopija(), izraz2->kopija());
}

// Implementacija metoda za klasu VeceJednako!

void VeceJednako::ispisi() const{
    cout << "(";
    izraz1->ispisi();
    cout << ") >= (";
    izraz2->ispisi();
    cout << ")";
}

Izraz *VeceJednako::izvod(char c) const{
    //Ovu funkciju necemo koristiti!
    return new VeceJednako();
}

double VeceJednako::izracunaj() const{ 
    return izraz1->izracunaj() >= izraz2->izracunaj();
}

Izraz *VeceJednako::kopija() const{
    return new VeceJednako(izraz1->kopija(), izraz2->kopija());
}

// Implementacija metoda za klasu Jednako!

void Jednako::ispisi() const{
    cout << "(";
    izraz1->ispisi();
    cout << ") == (";
    izraz2->ispisi();
    cout << ")";
}

Izraz *Jednako::izvod(char c) const{
    //Ovu funkciju necemo koristiti!
    return new Jednako();
}

double Jednako::izracunaj() const{ 
    return izraz1->izracunaj() == izraz2->izracunaj();
}

Izraz *Jednako::kopija() const{
    return new Jednako(izraz1->kopija(), izraz2->kopija());
}

// Implementacija metoda za klasu Razlicito!

void Razlicito::ispisi() const{
    cout << "(";
    izraz1->ispisi();
    cout << ") == (";
    izraz2->ispisi();
    cout << ")";
}

Izraz *Razlicito::izvod(char c) const{
    //Ovu funkciju necemo koristiti!
    return new Razlicito();
}

double Razlicito::izracunaj() const{ 
    return izraz1->izracunaj() != izraz2->izracunaj();
}

Izraz *Razlicito::kopija() const{
    return new Razlicito(izraz1->kopija(), izraz2->kopija());
}