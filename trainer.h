#ifndef TRAINER_H
#define TRAINER_H
#include "network.h"
#include <ctime>
#include <math.h>
#include <iostream>

using namespace std;

struct Trainer{
    Network *n;
    unsigned int length;
    double randomness;
    unsigned int currentNet;
    Trainer();
    Trainer(Network n,double randomness,unsigned int population = 5);
    ~Trainer();
    Network &update(double fitness, double randomness);
    void randomize(double randomness);
};

#endif // TRAINER_H
