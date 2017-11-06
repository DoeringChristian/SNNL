#include "matrixd.h"

Matrixd::Matrixd(){
    
}
Matrixd::Matrixd(unsigned int width, unsigned int height){
    this->width = width;
    this->height = height;
    this->matrix = new double*[width];
    for(int i = 0;i < width;i++)
        matrix[i] = new double[height];
    for(int i = 0;i < width;i++)
        for(int j = 0;j < height;j++)
            matrix[i][j] = 0;
}
Matrixd::Matrixd(const Matrixd &copy){
    this->width = copy.width;
    this->height = copy.height;
    this->matrix = new double*[width];
    for(int i = 0;i < width;i++)
        matrix[i] = new double[height];
    for(int i = 0;i < width;i++)
        for(int j = 0;j < height;j++)
            matrix[i][j] = copy.matrix[i][j];
}
Matrixd::~Matrixd(){
    for(int i = 0;i < this->width;i++){
        for(int j = 0;j < this->height;j++)
            delete &this->matrix[i][j];
        delete &this->matrix[i];
    }
}

double* Matrixd::operator [](unsigned int x) const{
    return this->matrix[x];
}

void Matrixd::operator =(const Matrixd &m){
    //delete
    for(int i = 0;i < this->width;i++){
        for(int j = 0;j < this->height;j++)
            delete &this->matrix[i][j];
        delete &this->matrix[i];
    }
    //new
    this->width = m.width;
    this->height = m.height;
    this->matrix = new double*[width];
    for(int i = 0;i < width;i++)
        matrix[i] = new double[height];
    for(int i = 0;i < width;i++)
        for(int j = 0;j < height;j++)
            matrix[i][j] = m.matrix[i][j];
}

unsigned int Matrixd::getHeight() const{
    return height;
}

unsigned int Matrixd::getWidth() const{
    return width;
}
