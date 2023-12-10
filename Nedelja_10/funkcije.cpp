#include "funkcije.hpp"
#include <map>
#include <cmath>

map<char, double> promenljive;

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
    for(char c: arg){
        if(c==id)
            return true;
    }

    return false;
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
    if(c==id){
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

//-----------------------------------------------
// Funkcija!

bool Funkcija::proveri() const{
    return izraz->proveri(argumenti);
}

void Funkcija::ispisi() const{
    izraz->ispisi();
    cout << endl;
}

double Funkcija::izracunaj() const{
    return izraz->izracunaj();
}

Izraz *Funkcija::izvod(char c) const{
    return izraz->izvod(c);
}

double Funkcija::operator[](vector<double>& arg){
    if(arg.size()!=argumenti.size()){
        cerr << "Greska pri pozivu funkcije!\n";
        exit(EXIT_FAILURE);
    }
    for(int i=0;i<argumenti.size();i++){
        promenljive[argumenti[i]]=arg[i];
    }

    return izraz->izracunaj();
}