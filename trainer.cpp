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
    randomize(randomness,2,0);
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

void Trainer::randomize(double randomness,double shift,uint start){
    for(uint i = start;i < this->length;i++)
        n[i].randomize(randomness,shift);           
}

Network &Trainer::update(double fitness, double randomness, double shift){
    this->n[currentNet].setFitness(fitness);
    if(currentNet >= length-1){
        Network tmp = n[0];
        Network tmp2 = n[0];
        uint t1 = 0;
        for(uint i = 0;i < length;i++)
            if(n[i].getFitness() < tmp.getFitness()){
                tmp = n[i];
                t1 = i;
            }
        for(uint i = 0;i < length;i++)
            if(n[i].getFitness() < tmp2.getFitness() && i != t1){
                tmp2 = n[i];
                cout << t1 << "|" << i << endl;
            }
        for(uint i = 0;i < length;i++)
            this->n[i] = tmp;
        for(uint i = 1;i < length;i++)
            this->n[i] += tmp2;
        this->currentNet = 0;
        randomize(randomness,shift,2);
    }
    else
        currentNet ++;
    return n[currentNet];
    
}

void Trainer::setRandomness(double randomness){
    this->randomness = randomness;
}










