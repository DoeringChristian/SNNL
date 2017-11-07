#ifndef VECTORD_H
#define VECTORD_H
#include "matrixd.h"
#include "m.h"
#define M_E 2.71828182846

class Matrixd;

class Vectord{
    //variables
    double* vect;
    unsigned int length;
public:
    //con-/de-structor
    Vectord();
    Vectord(unsigned int length);
    Vectord(const Vectord &copy);
    ~Vectord();
    //operators
    double& operator[](unsigned int index) const;
    Vectord operator*(const Matrixd &m) const;
    void operator =(const Vectord &v);
    //getters
    unsigned int size() const;
};

Vectord sig(const Vectord& s);
double sig(double d);

#endif // VECTORD_H
