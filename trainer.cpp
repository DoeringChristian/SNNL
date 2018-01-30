#include "trainer.h"

Trainer::Trainer(){
    this->length = 0;
    this->randomness = 0;
    this->networks = 0;
}

Trainer::Trainer(Network n, double randomness, unsigned int population){
    srand(time(0));
    this->randomness = randomness;
    this->networks = new Network[population];
    this->length = population;
    for(uint i = 0;i < population;i++)
        this->networks[i] = n;
    this->currentNet = 0;
    randomize(randomness,2,1);
}

Trainer::~Trainer(){
    delete [] networks;
}

Network &Trainer::operator[](uint index) const{
    return networks[index];
}

uint Trainer::size() const{
    return this->length;
}

Network &Trainer::current() const{
    return networks[currentNet];
}

void Trainer::randomize(double randomness,double shift,uint start){
    for(uint i = start;i < this->length;i++)
        networks[i].randomize(randomness,shift);           
}

Network &Trainer::update(double fitness, double randomness, double shift){
    this->networks[currentNet].setFitness(fitness);
    if(currentNet >= length-1){
        Network tmp = networks[0];
        Network tmp2 = networks[0];
        uint t1 = 0;
        for(uint i = 0;i < length;i++)
            if(networks[i].getFitness() < tmp.getFitness()){
                tmp = networks[i];
                t1 = i;
            }
        for(uint i = 0;i < length;i++)
            if(networks[i].getFitness() < tmp2.getFitness() && i != t1)
                tmp2 = networks[i];
        for(uint i = 0;i < length;i++)
            this->networks[i] = tmp;
        for(uint i = 1;i < length;i++)
            this->networks[i] += tmp2;
        this->currentNet = 0;
        randomize(randomness,shift,2);
    }
    else
        currentNet ++;
    return networks[currentNet];
    
}

void Trainer::setRandomness(double randomness){
    this->randomness = randomness;
}










