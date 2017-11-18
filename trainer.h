#ifndef TRAINER_H
#define TRAINER_H
#include "network.h"
#include <ctime>
#include <math.h>
#include <iostream>

using namespace std;

class Trainer{
    Network *n;
    unsigned int length;
    double randomness;
    unsigned int currentNet;
public:
    Trainer();
    Trainer(Network n,double randomness,unsigned int population = 5);
    ~Trainer();
    Network &operator[](uint index) const;
    uint size() const;
    Network &current() const;
    Network &update(double fitness, double randomness);
    void randomize(double randomness);
    void setRandomness(double randomness);
};

#endif // TRAINER_H
