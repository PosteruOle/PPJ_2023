#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>

using namespace std;

class Complex{
    public:
    Complex(){ }
    
    Complex(int x, int y){
        real=x;
        imag=y;
    }
    
    Complex(Complex &z){
        real=z.getReal();
        imag=z.getImag();
    }

    int getReal(){
        return real;
    }

    int getImag(){
        return imag;
    }

    private:
    int real;
    int imag;
};

ostream& operator<<(ostream& buffer, Complex& z){
    buffer << z.getReal() << " + " << z.getImag() << "i\n";
    return buffer;
}

ostream& operator<<(ostream& buffer, Complex* z){
    buffer << z->getReal() << " + " << z->getImag() << "i\n";
    return buffer;
}

Complex& operator+(Complex& z1, Complex& z2){
    Complex *result=new Complex(z1.getReal()+z2.getReal(), z1.getImag()+z2.getImag());
    return *result;
}

Complex& operator-(Complex& z1, Complex& z2){
    Complex *result=new Complex(z1.getReal()-z2.getReal(), z1.getImag()-z2.getImag());
    return *result;
}

Complex& operator*(Complex& z1, Complex& z2){
    Complex *result=new Complex(z1.getReal()*z2.getReal()-z1.getImag()*z2.getImag(), z1.getImag()*z2.getReal()+z2.getImag()*z1.getReal());
    return *result;
}

int main(){

    Complex *z1=new Complex(1, 3);
    Complex z2(1, 3);
    Complex z3(2, 5);
    Complex z4=z3;
    cout << "z1 = " << z1;
    cout << "z2 = " << z2;
    cout << "z3 = " << z3;
    cout << "z4 = " << z4;
    cout << "z1+z2 = " << *z1+z2;
    cout << "z3+z2 = " << z3+z2;
    cout << "z3-z2 = " << z3-z2;
    cout << "z2*z3 = " << z2*z3; 

    return 0;
}
