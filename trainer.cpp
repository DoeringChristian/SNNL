#include "trainer.h"

Trainer::Trainer(){
    this->length = 0;
    this->randomness = 0;
    this->n = 0;
}

Trainer::Trainer(Network n, double randomness, unsigned int population){
    srand(time(0));
    this->randomness = randomness;
    this->n = new Network[population];
    this->length = population;
    for(uint i = 0;i < population;i++)
        this->n[i] = n;
    this->currentNet = 0;
    randomize(randomness);
}

Trainer::~Trainer(){
    delete [] n;
}

Network &Trainer::operator[](uint index) const{
    return n[index];
}

uint Trainer::size() const{
    return this->length;
}

Network &Trainer::current() const{
    return n[currentNet];
}

void Trainer::randomize(double randomness){
    for(uint i = 1;i < this->length;i++)
        n[i].randomize(randomness);           
}

Network &Trainer::update(double fitness,double randomness){
    this->n[currentNet].setFitness(fitness);
    if(currentNet >= length-1){
        Network tmp = n[0];
        for(uint i = 0;i < length;i++)
            if(n[i].getFitness() < tmp.getFitness())
                tmp = n[i];
        for(uint i = 0;i < length;i++)
            this->n[i] = tmp;
        this->currentNet = 0;
        randomize(randomness);
    }
    else
        currentNet ++;
    return n[currentNet];
    
}

void Trainer::setRandomness(double randomness){
    this->randomness = randomness;
}










