#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>

using namespace std;

class Razlomak{
    public:
    Razlomak(){ }

    Razlomak(int brojilac, int imenilac) : _brojilac(brojilac), _imenilac(imenilac) { }
    
    Razlomak(Razlomak& r){
        _imenilac=r.getImenilac();
        _brojilac=r.getBrojilac();
    }

    int getBrojilac(){
        return _brojilac;
    }

    int getImenilac(){
        return _imenilac;
    }

    void skratiRazlomak(){
        for(int i=2;i<=_brojilac;i++){
            while(_brojilac%i==0 && _imenilac%i==0){
                _brojilac/=i;
                _imenilac/=i;
            }
        }
    }

    void invertuj(){
        int help=_imenilac;
        _imenilac=_brojilac;
        _brojilac=help;
    }

    Razlomak& operator*(int c){
        Razlomak *result=new Razlomak(c*_brojilac, _imenilac);
        return *result;
    }
    private:
    int _brojilac;
    int _imenilac;
};

ostream& operator<<(ostream& buffer, Razlomak& r){
    if(r.getImenilac()==0){
        cerr << "Nije dozvoljeno deljenje nulom!\n";
        exit(EXIT_FAILURE);
    }
    
    r.skratiRazlomak();

    if(r.getBrojilac()%r.getImenilac()==0){
        buffer << r.getBrojilac()/r.getImenilac() << "\n";
        return buffer;
    }
    
    buffer << r.getBrojilac() << "/" << r.getImenilac() << "\n";
    return buffer;
}

ostream& operator<<(ostream& buffer, Razlomak* r){
    if(r->getImenilac()==0){
        cerr << "Nije dozvoljeno deljenje nulom!\n";
        exit(EXIT_FAILURE);
    }

    r->skratiRazlomak();
    
    if(r->getBrojilac()%r->getImenilac()==0){
        buffer << r->getBrojilac()/r->getImenilac() << "\n";
        return buffer;
    }
    
    buffer << r->getBrojilac() << "/" << r->getImenilac() << "\n";
    return buffer;
}

Razlomak& operator+(Razlomak &r1, Razlomak &r2){
    Razlomak *result=new Razlomak(r1.getBrojilac()*r2.getImenilac()+r1.getImenilac()*r2.getBrojilac(), r1.getImenilac()*r2.getImenilac());
    return *result;
}

Razlomak& operator-(Razlomak &r1, Razlomak &r2){
    Razlomak *result=new Razlomak(r1.getBrojilac()*r2.getImenilac()-r1.getImenilac()*r2.getBrojilac(), r1.getImenilac()*r2.getImenilac());
    return *result;
}

Razlomak& operator*(Razlomak &r1, Razlomak &r2){
    Razlomak *result=new Razlomak(r1.getBrojilac()*r2.getBrojilac(), r1.getImenilac()*r2.getImenilac());
    return *result;
}

Razlomak& operator/(Razlomak &r1, Razlomak &r2){
    Razlomak *result=new Razlomak(r1.getBrojilac()*r2.getImenilac(), r1.getImenilac()*r2.getBrojilac());
    return *result;
}

bool operator!=(Razlomak &r1, Razlomak &r2){
    if(r1.getImenilac()==0 || r2.getImenilac()==0){
        cerr << "Nije dozvoljeno deljenje nulom!\n";
        exit(EXIT_FAILURE);
    }
    double value1=(1.0*r1.getBrojilac())/r1.getImenilac();
    double value2=(1.0*r2.getBrojilac())/r2.getImenilac();
    if(value1==value2)
        return false;
    else
        return true;    
}

bool operator==(Razlomak &r1, Razlomak &r2){
    if(r1.getImenilac()==0 || r2.getImenilac()==0){
        cerr << "Nije dozvoljeno deljenje nulom!\n";
        exit(EXIT_FAILURE);
    }
    double value1=(1.0*r1.getBrojilac())/r1.getImenilac();
    double value2=(1.0*r2.getBrojilac())/r2.getImenilac();
    if(value1==value2)
        return true;
    else
        return false;    
}

int main(){

    Razlomak *r1=new Razlomak(1, 2);
    Razlomak r2(2, 4);
    Razlomak r3(7, 8);
    int c;
    cout << "r1 = " << r1;
    cout << "r2 = " << r2; 
    cout << "r3 = " << r3;
    cout << "--------------------------------\n";
    cout << "r2+r3 = " << r2+r3;
    cout << "r2-r3 = " << r2-r3;
    cout << "r2*r3 = " << r2*r3;
    cout << "r3/r2 = " << r3/r2;
    cout << "--------------------------------\n";
    cout << "r2!=r3 <=> " << (r2!=r3) << "\n";
    cout << "r2==r3 <=> " << (r2==r3) << "\n";
    cout << "r2==r2 <=> " << (r2==r2) << "\n";
    cout << "--------------------------------\n";
    cout << "r2!=r3 <=> " << (r2!=r3) << "\n";
    cout << "Unesite skalar kojim zelite da pomnozite razlomak: \n";
    cin >> c;
    cout << "c*r1 = " << (*r1*c);
    cout << "c*r2 = " << r2*c; 
    cout << "c*r3 = " << r3*c;
    cout << "---------------------------------\n";
    cout << "r1 = " << r1;
    cout << "r2 = " << r2; 
    cout << "r3 = " << r3;
    r1->invertuj();
    r2.invertuj();
    r3.invertuj();
    cout << "---------------------------------\n";
    cout << "r1 = " << r1;
    cout << "r2 = " << r2; 
    cout << "r3 = " << r3;

    return 0;
}