#ifndef TRAINER_H
#define TRAINER_H
#include "network.h"
#include <ctime>
#include <math.h>
#include <iostream>

enum Reproduction{
    SOF,
    First_Second,
    First_Third,
    SOF_First_Second,
    SOF_First_Third,
    Cross,
    SOF_Cross,
    SOF_First_Second_Third
};

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
    Reproduction rep;
public:
    unsigned int currentNet;
    Trainer();
    Trainer(Network n,double randomness,Reproduction rep = SOF,unsigned int population = 5);
    ~Trainer();
    Network &operator[](uint index) const;
    uint size() const;
    Network &current() const;
    Network &update(double fitness, double randomness,double shift);
    void randomize(double randomness, double shift, uint start);
    void setRandomness(double randomness);
};

#endif // TRAINER_H
