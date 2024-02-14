#ifndef __IZRAZI_HPP__
#define __IZRAZI_HPP__

#include <iostream>
#include <cstdlib>
#include <string>
#include <map>

using namespace std;

class Izraz{
public:
  virtual string izracunaj() const =0;
};

class Konstanta: public Izraz{
public:
  Konstanta(){ }
  Konstanta(string vrednost){
    _vrednost=vrednost;
  }
  string izracunaj() const;
  string _vrednost;
};

class Promenljiva: public Izraz{
public:
  Promenljiva(){ }
  Promenljiva(string id){
    _id=id;
  }
  Promenljiva(string id, string value){
    _id=id;
    _value=value;
  }
  string izracunaj() const;
  string _id;
  string _value;
};

class UnarniIzraz : public Izraz{
public:
  UnarniIzraz(){ }
  UnarniIzraz(string operacija, Izraz *izraz){
    _operacija=operacija;
    _izraz=izraz;
  }
  string izracunaj() const;
  string _operacija;
  Izraz *_izraz;
};

class BinarniIzraz: public Izraz{
public:
  BinarniIzraz(){ }
  BinarniIzraz(string operacija, Izraz *izraz1, Izraz * izraz2){
    _operacija=operacija;
    _izraz1=izraz1;
    _izraz2=izraz2;
  }
  string izracunaj() const;
  string _operacija;
  Izraz *_izraz1;
  Izraz *_izraz2;
};

#endif