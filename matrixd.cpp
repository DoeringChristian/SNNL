#include "matrixd.h"

Matrixd::Matrixd(){
    width = 0;
    height = 0;
    matrix = 0;
}
Matrixd::Matrixd(unsigned int width, unsigned int height){
    this->width = width;
    this->height = height;
    this->matrix = new double*[width];
    for(uint i = 0;i < width;i++)
        matrix[i] = new double[height];
    for(uint i = 0;i < width;i++)
        for(uint j = 0;j < height;j++)
            matrix[i][j] = 0;
}
Matrixd::Matrixd(const Matrixd &copy){
    this->width = copy.width;
    this->height = copy.height;
    this->matrix = new double*[width];
    for(uint i = 0;i < width;i++)
        matrix[i] = new double[height];
    for(uint i = 0;i < width;i++)
        for(uint j = 0;j < height;j++)
            matrix[i][j] = copy.matrix[i][j];
}
Matrixd::~Matrixd(){
    for(uint i = 0;i < this->width;i++)
        delete [] this->matrix[i];
    delete [] this->matrix;
}

double* Matrixd::operator [](unsigned int x) const{
    return this->matrix[x];
}

void Matrixd::operator =(const Matrixd &m){
    if(&m == this)
        return;
    //delete
    for(uint i = 0;i < this->width;i++)
        delete [] this->matrix[i];
    delete [] this->matrix;
    //new
    this->width = m.width;
    this->height = m.height;
    this->matrix = new double*[width];
    for(uint i = 0;i < width;i++)
        matrix[i] = new double[height];
    for(uint i = 0;i < width;i++)
        for(uint j = 0;j < height;j++)
            matrix[i][j] = m.matrix[i][j];
}

unsigned int Matrixd::getHeight() const{
    return height;
}

unsigned int Matrixd::getWidth() const{
    return width;
}

bool Matrixd::operator ==(const Matrixd &comp) const{
    if(this->getHeight() != comp.getHeight())
        return false;
    if(this->getWidth() != comp.getWidth())
        return false;
    for(uint i = 0;i < width;i++)
        for(uint j = 0;j < height;j++)
            if(this->matrix[i][j] != comp[i][j])
                return false;
    return true;
}
