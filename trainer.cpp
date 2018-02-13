#include "trainer.h"

Trainer::Trainer(){
    this->length = 0;
    this->networks = 0;
}

Trainer::Trainer(Network n, uint population){
    srand(time(0));
    this->length = population;
    networks = new Network[population];
    for(uint i = 0;i < length;i++)
        networks[i] = n;
    for(uint i = 1;i < length;i++)
        networks[i].randomize(1,2);
    resetFitness();
}

Trainer::~Trainer(){
    delete [] networks;
}

Network &Trainer::operator [](uint index) const{
    return networks[index];
}

uint Trainer::size() const{
    return this->length;
}

void Trainer::update(double randomness, double shift){
    Network *best = &networks[0];
    Network *best2 = &networks[0];
    for(uint i = 0;i < length;i++)
        if(networks[i].getFitness() < best->getFitness())
            best = &networks[i];
    for(uint i = 0;i < length;i++)
        if(networks[i].getFitness() < best2->getFitness() && &networks[i] != best)
            best2 = &networks[i];
    Network n = *best;
    Network n2 = *best2;
    for(uint i = 0;i < length;i++)
        networks[i] = n;
    for(uint i = 1;i < length;i++){
        networks[i] += n2;
        networks[i].randomize(randomness,shift);
    }
    networks[0] = n;
}

uint Trainer::best() const{
    uint best = 0;
    for(uint i = 0;i < length;i++)
        if(networks[i].getFitness() < networks[best].getFitness())
            best = i;
    return best;
}

void Trainer::resetFitness(){
    for(uint i = 0;i < length;i++)
        networks[i].setFitness(0);
}






















