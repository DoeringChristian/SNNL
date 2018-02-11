#include "trainer.h"

Trainer::Trainer(){
    this->length = 0;
    this->randomness = 0;
    this->networks = 0;
    rep = SOF;
}

Trainer::Trainer(Network n, double randomness, Reproduction rep, unsigned int population){
    srand(time(0));
    this->randomness = randomness;
    this->networks = new Network[population];
    this->length = population;
    for(uint i = 0;i < population;i++)
        this->networks[i] = n;
    this->currentNet = 0;
    randomize(randomness,2,1);
    this->rep = rep;
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
        Network sorted[length];
        for(uint i = 0;i < length;i++)
            sorted[i] = networks[i];
        for(uint i = 0;i < length;i++){
            uint k = i;
            for(uint j = i;j < length;j++)
                if(networks[j].getFitness() < networks[k].getFitness())
                    k = j;
            Network first = sorted[i];
            sorted[i] = sorted[k];
            sorted[k] = first;
        }
        for(uint i = 0;i < length;i++)
            networks[i] = sorted[0];
#ifdef OUTPUT
        for(uint i = 0;i < length;i++)
            cout << sorted[i].getFitness() << "|";
        cout << endl;
#endif
        //Reproduction Methodes:
        switch(rep){
        case SOF:
            for(uint i = 1;i < length;i++)
                randomize(randomness,shift,1);
            break;
        case First_Second:
            for(uint i = 0;i < length;i++)
                networks[i] += sorted[1];
            randomize(randomness,shift,1);
            break;
        case First_Third:
            for(uint i = 0;i < length;i++)
                networks[i] += sorted[2];
            break;
        case SOF_First_Second:
            for(uint i = 1;i < length;i++)
                networks[i] += sorted[1];
            randomize(randomness,shift,2);
            break;
        case SOF_First_Third:
            for(uint i = 1;i < length;i++)
                networks[i] += sorted[2];
            randomize(randomness,shift,2);
            break; 
        }
        this->currentNet = 0;
    }
    else
        currentNet ++;
    return networks[currentNet];
    
}

void Trainer::setRandomness(double randomness){
    this->randomness = randomness;
}










