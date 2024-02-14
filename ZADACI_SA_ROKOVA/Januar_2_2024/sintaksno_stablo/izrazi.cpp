#include "izrazi.hpp"

extern map<string, string> promenljive;

string Konstanta::izracunaj() const{
  string tmp=_vrednost.substr(1, _vrednost.size()-2);
  return tmp;
}

string Promenljiva::izracunaj() const{
  if(promenljive.find(_id)==promenljive.end()){
    cerr << "Promenljiva nije definisana!\n";
    exit(EXIT_FAILURE);
  }
  return promenljive[_id];
}

string UnarniIzraz::izracunaj() const{
  if(_operacija=="~"){
    string tmp=_izraz->izracunaj();
    string result="";
    int n=tmp.size();
    for(int i=n-1;i>=0;i--){
      result+=tmp[i];
    }
    return result;
  } else {
    cerr << "Prosledjeni unarni operator nije definisan!\n";
    exit(EXIT_FAILURE);
  }
}

string BinarniIzraz::izracunaj() const{
  if(_operacija=="+"){
    return _izraz1->izracunaj()+_izraz2->izracunaj();
  } else if(_operacija=="*"){
    string tmp1=_izraz1->izracunaj();
    string tmp2=_izraz2->izracunaj();
    string result="";
    int i=0;
    while(tmp1[i]==tmp2[i]){
      result+=tmp1[i];
      i++;
    }
    return result;
  } else if(_operacija=="=="){
    if(_izraz1->izracunaj()==_izraz2->izracunaj()){
      return "1";
    } else {
      return "0";
    }
  } else if(_operacija=="!="){
    if(_izraz1->izracunaj()!=_izraz2->izracunaj()){
      return "1";
    } else {
      return "0";
    }
  } else {
    cerr << "Prosledjeni binarni operator nije definisan!\n";
    exit(EXIT_FAILURE);
  }
}