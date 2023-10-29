/*
Ovaj fajl sadrži implementaciju klase Polinom.
Neke od implementiranih metoda su: sabiranje, oduzimanje i množenje polinoma, 
računanje izvoda polinoma, računje integrala polinoma, izračunavanje vrednosti polinoma u datoj tački...
U main funkciji su testirani pomenuti metodi!
*/
#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>

using namespace std;

class Polinom{
    public:
    Polinom(){ }

    Polinom(vector<int>& v){
        koeficijenti=v;
    }
    
    Polinom(Polinom *p){
        koeficijenti=p->getKoeficijent();
    }
    
    Polinom(Polinom &p){
        koeficijenti=p.getKoeficijent();
    }

    vector<int> getKoeficijent() const{
        return koeficijenti;
    }

    void izvod(){
        koeficijenti.pop_back();
        int i=koeficijenti.size()-1;
        for(;i>=0;i--){
            koeficijenti[i]*=koeficijenti.size()-i;
        }    
    }

    void integral(){
        koeficijenti.push_back(0);
        int i=koeficijenti.size()-2;
        for(;i>=0;i--){
            koeficijenti[i]/=koeficijenti.size()-i-1;
        } 
    }

    double vrednost(double x){
        double result=0;
        int n=koeficijenti.size();
        int p=1;
        result+=koeficijenti[n-1];
        for(int i=n-2;i>=0;i--){
            p*=x;
            result+=p*koeficijenti[i];
        }
        return result;
    }

    void operator*(int x){
        int n=koeficijenti.size();
        for(int i=0;i<n;i++){
            koeficijenti[i]*=x;
        }
    }

    int operator[](int p){
        int n=koeficijenti.size();
        if(p<0 || p>=n){
            cerr << "Index out of bounds!\n";
            return INT16_MIN;
        }
        return koeficijenti[p];
    }

    void operator=(const Polinom &p){
        koeficijenti=p.getKoeficijent();
    }
    
    Polinom operator/(Polinom& p){
        Polinom *result=new Polinom();
        return *result;
    }
    private:
    vector<int> koeficijenti;
};

ostream& operator<<(ostream& buffer, Polinom *p){
    vector<int> v=p->getKoeficijent();
    int n=v.size();
    if(n==0){
        buffer << "0\n";
        return buffer;
    }
    for(int i=0;i<n;i++){
        if(i==n-1){
            buffer << v[i] << "\n";
            break;
        }
        buffer << v[i] << "*" << "x^" << (n-1-i) << " + ";
    }

    return buffer;
}

ostream& operator<<(ostream& buffer, Polinom p){
    vector<int> v=p.getKoeficijent();
    int n=v.size();
    if(n==0){
        buffer << "0\n";
        return buffer;
    }
    for(int i=0;i<n;i++){
        if(i==n-1){
            buffer << v[i] << "\n";
            break;
        }
        buffer << v[i] << "*" << "x^" << (n-1-i) << " + ";
    }

    return buffer;
}

Polinom& operator+(const Polinom& p1, const Polinom& p2){
    vector<int> v1=p1.getKoeficijent();
    vector<int> v2=p2.getKoeficijent();
    int n=v1.size();
    int m=v2.size();
    vector<int> result;
    int max=0;
    if(n>m){
        result.resize(n);
        max=n;
    } else {
        result.resize(m);
        max=m;
    }
        int i=n-1;
        int j=m-1;
        int k=max-1;
        while(i>=0 && j>=0){
            result[k]=v1[i]-v2[j];
            i--;
            j--;
            k--;    
        }
        while(i>=0){
           result[k]=v1[i];
            i--;
            k--; 
        }
        while(j>=0){
           result[k]=v2[j];
            j--;
            k--; 
        }
        Polinom *zbir=new Polinom(result);
        return *zbir;    
}

Polinom& operator-(const Polinom& p1, const Polinom& p2){
    vector<int> v1=p1.getKoeficijent();
    vector<int> v2=p2.getKoeficijent();
    int n=v1.size();
    int m=v2.size();
    vector<int> result;
    int max=0;
    if(n>m){
        result.resize(n);
        max=n;
    } else {
        result.resize(m);
        max=m;
    }
        int i=n-1;
        int j=m-1;
        int k=max-1;
        while(i>=0 && j>=0){
            result[k]=v1[i]-v2[j];
            i--;
            j--;
            k--;    
        }
        while(i>=0){
           result[k]=v1[i];
            i--;
            k--; 
        }
        while(j>=0){
           result[k]=-1*v2[j];
            j--;
            k--; 
        }
        Polinom *razlika=new Polinom(result);
        return *razlika;    
}

Polinom& operator*(const Polinom& p1, const Polinom& p2){
        vector<int> v1=p2.getKoeficijent();
        vector<int> v2=p2.getKoeficijent();
        int n=v1.size();
        int m=v2.size();
        vector<int> result_v(n+m-1, 0);
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                result_v[i+j]+=v1[i]*v2[j];
            }
        }
        Polinom *result=new Polinom(result_v);
        return *result;
    }

int main(){

    vector<int> coef1={1, 2, 3};
    vector<int> coef2={1, 2, 3, 4};
    vector<int> coef3={1, 2};
    Polinom p1(coef1);
    Polinom p2(coef2);
    Polinom p3(coef3);
    double x;
    int p;
    int c;
    cout << "p1 = " << p1;
    cout << "p2 = " << p2;
    cout << "p3 = " << p3;
    cout << "p1+p2 =" << p1+p2;
    cout << "p2-p1 =" << p2-p1;
    Polinom p_mul=p1*p3;
    cout << "p1*p3 = " << p_mul;
    cout << "p1*p3 = " << p1*p3;
    p3.izvod();
    p2.izvod();
    p1.izvod();
    cout << "(p3)' = " << p3;
    cout << "(p2)' = " << p2;
    cout << "(p1)' = " << p1;
    p3.integral();
    p2.integral();
    p1.integral();
    cout << "S(p3)dx = " << p3;
    cout << "S(p2)dx = " << p2;
    cout << "S(p1)dx = " << p1;
    cout << "Unesite tacku u kojoj zelite da pronadjete vrednost polinoma: \n";
    cin >> x;
    cout << "p1(x) = " << p1.vrednost(x) << "\n";
    cout << "p2(x) = " << p2.vrednost(x) << "\n";
    cout << "p3(x) = " << p3.vrednost(x) << "\n";
    cout << "Koji koeficijent vam je potreban: \n";
    cin >> p;
    cout << "p1[" << p << "] = " << p1[p] << "\n"; 
    cout << "p2[" << p << "] = " << p2[p] << "\n"; 
    cout << "p3[" << p << "] = " << p3[p] << "\n"; 
    cout << "Unesite skalar kojim zelite da pomnozite koeficijente: \n";
    cin >> c;
    cout << "p1 = " << p1;
    cout << "p2 = " << p2;
    cout << "p3 = " << p3;
    p1*c;
    p2*c;
    p3*c;
    cout << c << "*p1 = " << p1;
    cout << c << "*p2 = " << p2;
    cout << c << "*p3 = " << p3;
    cout << "----------------------------------------------------------\n";
    Polinom p10=p3;
    cout << "p10 = " << p10;

    return 0;
}