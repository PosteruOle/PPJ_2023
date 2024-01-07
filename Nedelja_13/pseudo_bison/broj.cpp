#include "broj.hpp"
#include <string>

using namespace std;

extern void yyerror(string s);

Broj::Broj(int x) {	
   _b.push_back(x);
}

Broj::Broj(const vector<int>& b) {
   _b = b;
}

Broj::Broj(const Broj& b) {
   _b = b._b;
}

int Broj::get_size() const {
   return _b.size();
}

void Broj::push_back(int x) {
  _b.push_back(x);
}

void Broj::show(ostream& s) const {
	
	if (_b.size() > 1) {
		s<<'[';
		for (auto it = _b.begin(); it != _b.end(); it++) {
			
			if (it != _b.begin())
				s<<", ";
			s<<*it;
		}
		s<<']'<<endl;
	}
	else {
		s<<_b[0]<<endl;
	}
}

void Broj::show(int base) const {
	
	if (_b.size() > 1) {
		printf("[");
		for (auto it = _b.begin(); it != _b.end(); it++) {
				
			if (it != _b.begin()) {
				printf(", ");
			}
			switch (base) {
			
			case 8:
				printf("0%o", *it);
				break;
			case 16:
				printf("0x%x", *it);
				break;
			default:
				yyerror("Nepodrzana osnova\n");
		}
		}
		printf("]\n");
	}
	else {
		switch (base) {
			
			case 8:
				printf("0%o\n", _b[0]);
				break;
			case 16:
				printf("0x%x\n", _b[0]);
				break;
			default:
				yyerror("Nepodrzana osnova\n");
		}
	}
}

bool Broj::operator ==(const Broj& b) const {
	
	if (_b.size() != b._b.size()) {
		return false;
	}
	
	for (int i = 0; i < _b.size(); i++) {
		if (_b[i] != b._b[i]) {
			return false;
		}
	}
	
	return true;
	
}
bool Broj::operator !=(const Broj& b) const {
	
	if (_b.size() != b._b.size()) {
		return true;
	}
	
	for (int i = 0; i < _b.size(); i++) {
		if (_b[i] != b._b[i]) {
			return true;
		}
	}
	
	return false;
}

Broj* Broj::operator +(const Broj& b) const {
	
	if (_b.size() != b._b.size()) {
		yyerror("Neodgovarajuce dimenzije\n");
	}
	
	Broj* noviBroj = new Broj();
	
	for (int i = 0; i < _b.size(); i++) {
		
		noviBroj->push_back(_b[i] + b._b[i]);
	}
	
	return noviBroj;
}
Broj* Broj::operator -(const Broj& b) const {
	
	if (_b.size() != b._b.size()) {
		yyerror("Neodgovarajuce dimenzije\n");
	}
	
	Broj* noviBroj = new Broj();
	
	for (int i = 0; i < _b.size(); i++) {
		
		noviBroj->push_back(_b[i] - b._b[i]);
	}
	
	return noviBroj;
}

Broj* Broj::operator *(const Broj& b) const {
	
	if (_b.size() != b._b.size()) {
		yyerror("Neodgovarajuce dimenzije\n");
	}
	
	Broj* noviBroj = new Broj();
	
	for (int i = 0; i < _b.size(); i++) {
		
		noviBroj->push_back(_b[i] * b._b[i]);
	}
	
	return noviBroj;
}

Broj* Broj::operator /(const Broj& b) const 
{
	
	if (_b.size() != b._b.size()) {
		yyerror("Neodgovarajuce dimenzije\n");
	}
	
	Broj* noviBroj = new Broj();
	
	for (int i = 0; i < _b.size(); i++) {
		
		noviBroj->push_back(_b[i] / b._b[i]);
	}
	
	return noviBroj;
}
Broj* Broj::operator %(const Broj& b) const {
	
	if (_b.size() != b._b.size()) {
		yyerror("Neodgovarajuce dimenzije\n");
	}
	
	Broj* noviBroj = new Broj();
	
	for (int i = 0; i < _b.size(); i++) {
		
		noviBroj->push_back(_b[i] % b._b[i]);
	}
	
	return noviBroj;
}
Broj* Broj::operator -() const {
	
	Broj* noviBroj = new Broj();
	
	for (int i = 0; i < _b.size(); i++) {
		
		noviBroj->push_back(-_b[i]);
	}
	
	return noviBroj;
}

Broj* Broj::operator <<(const Broj& b) const {
	
	if (_b.size() != b._b.size()) {
		yyerror("Neodgovarajuce dimenzije\n");
	}
	
	Broj* noviBroj = new Broj();
	
	for (int i = 0; i < _b.size(); i++) {
		
		if (b._b[i] < 0) {
			yyerror("Mora biti > 0.");
		}
		
		noviBroj->push_back(_b[i] << b._b[i]);
	}
	
	return noviBroj;
}
Broj* Broj::operator >>(const Broj& b) const {
	
	if (_b.size() != b._b.size()) {
		yyerror("Neodgovarajuce dimenzije\n");
	}
	
	Broj* noviBroj = new Broj();
	
	for (int i = 0; i < _b.size(); i++) {
		
		if (b._b[i] < 0) {
			yyerror("Mora biti > 0.");
		}
		
		noviBroj->push_back(_b[i] >> b._b[i]);
	}
	
	return noviBroj;
}
Broj* Broj::operator &(const Broj& b) const {
	
	if (_b.size() != b._b.size()) {
		yyerror("Neodgovarajuce dimenzije\n");
	}
	
	Broj* noviBroj = new Broj();
	
	for (int i = 0; i < _b.size(); i++) {
		
		noviBroj->push_back(_b[i] & b._b[i]);
	}
	
	return noviBroj;
}
Broj* Broj::operator ^(const Broj& b) const {
	
	if (_b.size() != b._b.size()) {
		yyerror("Neodgovarajuce dimenzije\n");
	}
	
	Broj* noviBroj = new Broj();
	
	for (int i = 0; i < _b.size(); i++) {
		
		noviBroj->push_back(_b[i] ^ b._b[i]);
	}
	
	return noviBroj;
}
Broj* Broj::operator |(const Broj& b) const {
	
	if(_b.size() != b._b.size()) {
	  yyerror("Neodgovarajuce dimenzije\n");
	}
	
	Broj* noviBroj=new Broj();
	
	for(int i=0;i<_b.size();i++) {
	   noviBroj->push_back(_b[i] | b._b[i]);
	}
	
	return noviBroj;
}
Broj* Broj::operator ~() const {
	
	Broj* noviBroj=new Broj();
	
	for(int i = 0;i<_b.size();i++) {
	   noviBroj->push_back(~_b[i]);
	}
	
	return noviBroj;
}

int Broj::operator [](int i) {
	return _b[i];
}

ostream& operator <<(ostream& s, const Broj& b) {
	b.show(s);
	return s;
}
