#ifndef NETWORK_H
#define NETWORK_H
#include "matrixd.h"
#include <iostream>
#include <fstream>
#include "trainer.h"
#include <stdlib.h>

using namespace std;

class Network{
    //variables
    unsigned int layers;
    unsigned int *nodes;
    double fitness;
    Matrixd *m;
    Vectord *v;
    Vectord *bias;
public:
    //con-/destructors
    Network();
    Network(unsigned int nodes[], unsigned int layers);
    Network(const Network &copy);
    ~Network();
    //operators
    void operator=(const Network &n);
    Matrixd &operator[](unsigned int index) const;
    Vectord &operator()(unsigned int index) const;
    //functions
    void update();
    unsigned int size() const;
    Vectord getOutput() const;
    void setInput(unsigned int index, double value);
    unsigned int sizeAt(unsigned int index) const;
    bool SavetoFile(const std::string file) const;
    bool LoadFile(const std::string file);
    double getFitness() const;
    void setFitness(double fitness);
    void randomize(double randomness);
};

#endif // NETWORK_H
