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

void Trainer::update(double randomness, double shift,double percentage,double swap_percentage){
    //sort
    Network tmp[length];
    for(uint i = 0;i < length;i++)
        tmp[i] = networks[i];
    for(uint i = 0;i < length;i++){
        uint k = i;
        for(uint j = i;j < length;j++)
            if(tmp[j].getFitness() < tmp[k].getFitness())
                k = j;
        Network n = tmp[i];
        tmp[i] = tmp[k];
        tmp[k] = n;
    }
    //add first two
    networks[0] = tmp[0];
    networks[1] = tmp[1];
    //crossing
    for(uint i = 2;i < length;i++){
        uint i1 = rand() % length,i2;
        do
            i2 = rand() % length;
        while(i1 == i2);
        networks[i] = tmp[i1];
        networks[i].cross(tmp[i2],swap_percentage);
    }
    //mutating
    for(uint i = 2;i < length;i++)
        if(rand()/(RAND_MAX+1.0) < percentage)
            networks[i].randomize(randomness,shift);
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






















