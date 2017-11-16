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
    for(int i = 0;i < population;i++)
        this->n[i] = n;
    this->currentNet = 0;
    randomize();
}

Trainer::~Trainer(){
    delete [] n;
}

void Trainer::randomize(){
    for(int i = 1;i < this->length;i++)
        for(int j = 0;j < this->n[i].size()-1;j++)
            for(int k = 0;k < this->n[i][j].getWidth();k++)
                for(int l = 0;l < this->n[i][j].getHeight();l++)
                    n[i][j][k][l] += (((double)rand() / (double)(RAND_MAX))*2-1)*randomness;
                    
}

Network &Trainer::update(double fitness){
    this->n[currentNet].setFitness(fitness);
    if(currentNet >= length){
        Network *tmp = &n[0];
        for(int i = 0;i < length;i++)
            if(n[i].getFitness() < tmp->getFitness())
                tmp = &n[i];
        for(int i = 0;i < length;i++)
            this->n[i] = *tmp;
        this->currentNet = 0;
        randomize();
    }
    else
        currentNet ++;
    return n[currentNet];
    
}












