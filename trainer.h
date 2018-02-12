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
public:
    Trainer();
    Trainer(Network n,uint population = 10);
    ~Trainer();
    Network &operator [](uint index) const;
    uint size() const;
    uint best() const;
    void update(double randomness,double shift);
    void resetFitness();
};

#endif // TRAINER_H
