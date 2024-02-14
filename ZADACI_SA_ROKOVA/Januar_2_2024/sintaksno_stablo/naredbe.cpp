#include "naredbe.hpp"

map<string, string> promenljive;

void Blok::izvrsi() const{
  for(Naredba *n: _naredbe){
    n->izvrsi();
  }
}

void Deklaracija::izvrsi() const{
  promenljive[_id]="";
}

void PrintALL::izvrsi() const{
  for(auto pair: promenljive){
    cout << pair.first << " = " << pair.second << endl;
  }
}

void Print::izvrsi() const{
  if(_bufer=="output"){
    cout << _izraz->izracunaj() << endl;
  } else if(_bufer=="error"){
    cerr << _izraz->izracunaj() << endl;
  } else {
    cerr << "Nepostojeci bafer!\n";
    exit(EXIT_FAILURE);
  }
}

void Input::izvrsi() const{
  if(promenljive.find(_id)==promenljive.end()){
    cerr << "Promenljiva nije definisana!\n";
    exit(EXIT_FAILURE);
  }
  string tmp;
  cin >> tmp;
  promenljive[_id]=tmp;
}

void Inicijalizacija::izvrsi() const{
  if(_opcija==1){
    promenljive[_id]=_izraz->izracunaj();
    return;
  }
  if(promenljive.find(_id)==promenljive.end()){
    cerr << "Promenljiva nije definisana!\n";
    exit(EXIT_FAILURE);
  }
  promenljive[_id]=_izraz->izracunaj();
}

void If::izvrsi() const{
  if(uslov->izracunaj()=="1"){
    naredba->izvrsi();
  }
}

void IfElse::izvrsi() const{
  if(uslov->izracunaj()=="1"){
    naredba1->izvrsi();
  } else {
    naredba2->izvrsi();
  }
}

void While::izvrsi() const{
  while(uslov->izracunaj()=="1"){
    naredba->izvrsi();
  }
}