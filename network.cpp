#include "network.h"

Network::Network(){}
Network::Network(unsigned int nodes[]){
    this->layers = sizeof(nodes)/sizeof(nodes[0]);
    this->v = new Vectord[layers];
    for(int i = 0;i < layers;i++)
        v[i] = Vectord(nodes[i]);
    this->m = new Matrixd[layers-1];
    for(int i = 0;i < layers-1;i++)
        m[i] = Matrixd(nodes[i],nodes[i+1]);
}
Network::~Network(){
    for(int i = 0;i < layers-1;i++){
        delete &v[i];
        delete &m[i];
    }
    delete &v[layers-1];
}
