#ifndef MATRIXD_H
#define MATRIXD_H
#include "vectord.h"

class Vectord;

class Matrixd{
    //variables
    unsigned int width,height;
public:
    double** matrix;
    //con-/de-structor
    Matrixd();
    Matrixd(unsigned int width, unsigned int height);
    Matrixd(const Matrixd& copy);
    ~Matrixd();
    //operators
    double* operator[](unsigned int x) const;
    void operator=(const Matrixd &m);
    //getters
    unsigned int getHeight() const;
    unsigned int getWidth() const;
};

#endif // MATRIXD_H
