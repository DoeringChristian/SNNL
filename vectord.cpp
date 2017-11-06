#include "vectord.h"

Vectord::Vectord(){
    
}
Vectord::Vectord(unsigned int length){
    this->length = length;
    this->vect = new double[length];
    for(int i = 0;i < length;i++)
        this->vect[i] = 0;
}
Vectord::Vectord(const Vectord &copy){
    this->length = copy.size();
    this->vect = new double[length];
    for(int i = 0;i < length;i++)
        this->vect[i] = copy[i];
}

Vectord::~Vectord(){
    for(int i = 0;i < this->length;i++)
        delete &vect[i];
}

double& Vectord::operator[](unsigned int index) const{
    return this->vect[index];
}

Vectord Vectord::operator *(const Matrixd &m) const{
    Vectord v(m.getHeight());
    for(int i = 0;i < m.getHeight();i++){
        double d = 0;
        for(int j = 0;j < m.getWidth();j++)
            d += m.matrix[j][i]*this->vect[j];
        v[i] = d;
    }
    return v;
}

void Vectord::operator =(const Vectord &v){
    for(int i = 0;i < this->size();i++)
        delete[] &this->vect[i];
    this->length = v.size();
    this->vect = new double[length];
    for(int i = 0;i < length;i++)
        this->vect[i] = v[i];
}

unsigned int Vectord::size() const{
    return length;
}


double sig(double d){
    return 1/(1+pow(M_E,d));
}

Vectord sig(const Vectord &s){
    Vectord v(s.size());
    for(int i = 0;i < s.size();i++)
        v[i] = sig(s[i]);
    return v;
}












