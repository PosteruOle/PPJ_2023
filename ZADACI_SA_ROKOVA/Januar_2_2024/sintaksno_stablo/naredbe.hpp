#ifndef __NAREDBE_HPP__
#define __NAREDBE_HPP__

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
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
  void addNaredba(Naredba *n){
    _naredbe.push_back(n);
  }
  void izvrsi() const;
private:  
  vector<Naredba*> _naredbe;
};

class Deklaracija : public Naredba{
public:
  Deklaracija(){ }
  Deklaracija(string id){
    _id=id;
  }
  void izvrsi() const;
  string _id;
};

class PrintALL : public Naredba{
public:
  PrintALL(){}
  void izvrsi() const;
};

class Inicijalizacija : public Naredba{
public:
  Inicijalizacija(){ }
  Inicijalizacija(string id, Izraz *izraz, int opcija){
    _id=id;
    _izraz=izraz;
    _opcija=opcija;
  }
  void izvrsi() const;
  int _opcija;
  string _id;
  Izraz *_izraz;
};

class Print : public Naredba{
public:
  Print(){ }
  Print(string bufer, Izraz *izraz){
    _bufer=bufer;
    _izraz=izraz;
  }
  void izvrsi() const;
  string _bufer;
  Izraz *_izraz;
};

class Input : public Naredba{
public:
  Input(){ }
  Input(string id){
    _id=id;
  }
  void izvrsi() const;
private:
  string _id;
};

class If : public Naredba{
public:
  If(){ }
  If(Izraz *uslov, Naredba *naredba){
    this->uslov=uslov;
    this->naredba=naredba;
  }
  void izvrsi() const;
  Izraz *uslov;
  Naredba *naredba;
};

class IfElse: public Naredba{
public:
  IfElse(){ }
  IfElse(Izraz *uslov, Naredba *naredba1, Naredba *naredba2){
    this->uslov=uslov;
    this->naredba1=naredba1;
    this->naredba2=naredba2;
  }
  void izvrsi() const;
  Izraz *uslov;
  Naredba *naredba1;
  Naredba *naredba2;
};

class While : public Naredba{
public:
  While(){ }
  While(Izraz *uslov, Blok *naredba){
    this->uslov=uslov;
    this->naredba=naredba;
  }
  void izvrsi() const;
  Izraz *uslov;
  Blok *naredba;
};


#endif