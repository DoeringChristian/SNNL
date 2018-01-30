#ifndef TRAINER_H
#define TRAINER_H
#include "network.h"
#include <ctime>
#include <math.h>
#include <iostream>

/*
 * Use minimal 3 agents per simulation
 * otherwise you will not have any mutation.
 */

using namespace std;

class Network;

class Trainer{
    Network *networks;
    unsigned int length;
    double randomness;
public:
    unsigned int currentNet;
    Trainer();
    Trainer(Network n,double randomness,unsigned int population = 5);
    ~Trainer();
    Network &operator[](uint index) const;
    uint size() const;
    Network &current() const;
    Network &update(double fitness, double randomness,double shift);
    void randomize(double randomness, double shift, uint start);
    void setRandomness(double randomness);
};

#endif // TRAINER_H
