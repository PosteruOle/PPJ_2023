#include "matrica.hpp"

void Matrica::ispisi(){
    int n=elements.size();
    int m=elements[0].size();
    for(int i=0;i<n;i++){
        cout << "\t";
        for(int j=0;j<m;j++){
            cout << elements[i][j] << " ";
        }
        cout << endl;
    }
}

Matrica *Matrica::saberi(Matrica *m){
    vector<vector<int>> matrix=m->getElements();
    vector<vector<int>> result;
    if(elements.size()!=matrix.size() || elements[0].size()!=matrix[0].size()){
        cerr << "Matrice nisu istih dimenzija!\n";
        exit(EXIT_FAILURE);
    }
    result.resize(elements.size());
    for(int i=0;i<elements.size();i++){
        result[i].resize(elements[0].size());
        for(int j=0;j<elements[0].size();j++){
            result[i][j]=elements[i][j]+matrix[i][j];
        }   
    }
    return new Matrica(result);
}

Matrica *Matrica::oduzmi(Matrica *m){
    vector<vector<int>> matrix=m->getElements();
    vector<vector<int>> result;
    if(elements.size()!=matrix.size() || elements[0].size()!=matrix[0].size()){
        cerr << "Matrice nisu istih dimenzija!\n";
        exit(EXIT_FAILURE);
    }
    result.resize(elements.size());
    for(int i=0;i<elements.size();i++){
        result[i].resize(elements[0].size());
        for(int j=0;j<elements[0].size();j++){
            result[i][j]=elements[i][j]-matrix[i][j];
        }   
    }
    return new Matrica(result);
}

Matrica *Matrica::pomnozi(Matrica *m){
    vector<vector<int>> result;
    vector<vector<int>> matrix=m->getElements(); 
    int n=elements.size();
    int s=elements[0].size();
    int k=matrix[0].size();
    if(s!=matrix.size()){
        cerr << "Matrice nisu odgovarajucih dimenzija! Ne mozemo ih pomnoziti!\n";
        exit(EXIT_FAILURE);
    }

    result.resize(n);

    for(int i=0;i<n;i++){
        result[i].resize(k);
        vector<int> tmp_r=elements[i];
        for(int j=0;j<k;j++){
            vector<int> tmp_c;
            for(int l=0;l<s;l++){
                tmp_c.push_back(matrix[l][j]);
            }
            int sum=0;
            for(int l=0;l<s;l++){
                sum+=tmp_r[l]*tmp_c[l];
            }
            result[i][j]=sum;
        }
    }
    return new Matrica(result);
}

Matrica *Matrica::pomnozi_pokoordinatno(Matrica *m){
    vector<vector<int>> matrix=m->getElements();
    vector<vector<int>> result;
    if(elements.size()!=matrix.size() || elements[0].size()!=matrix[0].size()){
        cerr << "Matrice nisu istih dimenzija!\n";
        exit(EXIT_FAILURE);
    }
    result.resize(elements.size());
    for(int i=0;i<elements.size();i++){
        result[i].resize(elements[0].size());
        for(int j=0;j<elements[0].size();j++){
            result[i][j]=elements[i][j]*matrix[i][j];
        }   
    }
    return new Matrica(result);
}

Matrica *Matrica::transponuj(){
    int n=elements.size();
    int m=elements[0].size();
    vector<vector<int>> result(m, vector<int>(n));
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            result[i][j]=elements[j][i];
        }
    }   

    return new Matrica(result);
}

void Matrica::addRow(vector<int>& v){
    elements.push_back(v);
}

int Matrica::getBrojRedova(){
    return elements.size();
}

int Matrica::getBrojKolona(){
    return elements[0].size();
}