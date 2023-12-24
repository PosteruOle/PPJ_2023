#include "polinomi.hpp"

void Polinom::ispisi() const{
    int n=_koeficijenti.size();
    if(n==0){
        cout << endl;
    }

    if(n==1){
        cout << _koeficijenti[0] << endl;
    }

    cout << _koeficijenti[0] << " ";
    for(int i=1;i<n;i++){
        if(i==n-1){
            if(_koeficijenti[i]>0){
            cout << "+ " << _koeficijenti[i] << "*x^" << i << endl;
            } else if(_koeficijenti[i]<0){
                cout << "- " << abs(_koeficijenti[i]) << "*x^" << i << endl;
            }
            break;
        }
        if(_koeficijenti[i]>0){
            cout << "+ " << _koeficijenti[i] << "*x^" << i << " ";
        } else if(_koeficijenti[i]<0){
            cout << "- " << abs(_koeficijenti[i]) << "*x^" << i << " ";
        }
    }
}

Polinom *Polinom::saberi(Polinom* p) const{
    vector<double> tmp=p->getKoeficijenti();
    int n=_koeficijenti.size();
    int m=tmp.size();
    int max;
    vector<double> result;
    if(n>m){
        max=n;
        result.resize(max, 0);
    } else {
        max=m;
        result.resize(max, 0);
    } 
    int i=0;
    int j=0;
    int k=0;
    while(i<n && j<m){
        result[k]=_koeficijenti[i]+tmp[j];
        i++;
        j++;
        k++;
    }

    while(i<n){
        result[k]=_koeficijenti[i];
        i++;
        k++;
    }

    while(j<m){
        result[k]=tmp[j];
        j++;
        k++;
    }
    return new Polinom(result);
}
Polinom *Polinom::oduzmi(Polinom* p) const{
    vector<double> tmp=p->getKoeficijenti();
    int n=_koeficijenti.size();
    int m=tmp.size();
    int max;
    vector<double> result;
    if(n>m){
        max=n;
        result.resize(max, 0);
    } else {
        max=m;
        result.resize(max, 0);
    } 
    int i=0;
    int j=0;
    int k=0;
    while(i<n && j<m){
        result[k]=_koeficijenti[i]-tmp[j];
        i++;
        j++;
        k++;
    }

    while(i<n){
        result[k]=_koeficijenti[i];
        i++;
        k++;
    }

    while(j<m){
        result[k]-=tmp[j];
        j++;
        k++;
    }
    return new Polinom(result);
}

Polinom *Polinom::negiraj() const{
    int n=_koeficijenti.size();
    vector<double> result(n);
    for(int i=0;i<n;i++){
        result[i]=-_koeficijenti[i];
    }
    return new Polinom(result);
}

bool Polinom::jednako(Polinom *p) const{
    vector<double> tmp=p->getKoeficijenti();
    int n=_koeficijenti.size();
    int m=tmp.size();
    if(n!=m)
        return false;
    for(int i=0;i<n;i++){
        if(_koeficijenti[i]!=tmp[i])
            return false;
    }
    return true;    
}

bool Polinom::razlicito(Polinom *p) const{
    /*
    vector<double> tmp=p->getKoeficijenti();
    int n=_koeficijenti.size();
    int m=tmp.size();
    if(n!=m)
        return true;
    for(int i=0;i<n;i++){
        if(_koeficijenti[i]!=tmp[i])
            return true;
    }
    return false;
    */
    return !jednako(p);
}

Polinom *Polinom::pomnozi(Polinom* p) const{
    vector<double> tmp=p->getKoeficijenti();
    vector<double> result;
    int n=_koeficijenti.size();
    int m=tmp.size();
    result.resize(n+m-1, 0);
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            result[i+j]+=_koeficijenti[i]*tmp[j];
        }
    }
    
    return new Polinom(result);
}

Polinom *Polinom::izvod() const{    
    int n=_koeficijenti.size();
    vector<double> result(n-1, 0);
    for(int i=1;i<n;i++){
        result[i-1]=_koeficijenti[i]*i;
    }
    return new Polinom(result);
}

Polinom *Polinom::integral(double x) const{
    int n=_koeficijenti.size();
    vector<double> result(n+1, 0);
    result[0]=x;
    for(int i=0;i<n;i++){
        result[i+1]=_koeficijenti[i]/(i+1);
    }
    return new Polinom(result);
}

double Polinom::operator[](double x) const{
    int n=_koeficijenti.size();
    int p=1;
    int result=0;
    for(int i=0;i<n;i++){
        result+=_koeficijenti[i]*p;
        p*=x;
    }
    return result;
}

double Polinom::vrednost(double x) const{
    int n=_koeficijenti.size();
    int p=1;
    int result=0;
    for(int i=0;i<n;i++){
        result+=_koeficijenti[i]*p;
        p*=x;
    }
    return result;
}