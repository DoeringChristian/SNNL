#include "network.h"

Network::Network(){
    this->layers = 0;
    this->m = 0;
}
Network::Network(unsigned int nodes[],unsigned int layers){
    this->layers = layers;
    this->input = Vectord(nodes[0]);
    this->output = Vectord(nodes[layers-1]);
    this->m = new Matrixd[layers-1];
    for(int i = 0;i < layers-1;i++)
        m[i] = Matrixd(nodes[i],nodes[i+1]);
}
Network::~Network(){
    delete [] this->m;
}

void Network::operator =(const Network &n){
    delete [] m;
    this->layers = n.size();
    this->input = n.input;
    this->output = n.output;
    this->m = new Matrixd[n.size()-1];
    for(int i = 0;i < layers-1;i++)
        m[i] = n[i];
}

Matrixd &Network::operator[](unsigned int index) const{
    return m[index];
}

void Network::update(){
    Vectord v = input;
    for(int i = 0;i < layers-1;i++) {
        v = sig(v*m[i]);
    }
    this->output = v;
}

unsigned int Network::size() const{
    return layers;
}

Vectord Network::getOutput() const{
    return output;
}

void Network::setInput(unsigned int index,double value){
    if(index < nodes[0])
        this->input[index] = value;
}

unsigned int Network::sizeAt(unsigned int index) const{
    if(index = layers-1)
        return output.size();
    else
        return m[index].getWidth();
}

double Network::fitness(const Vectord &comp) const{
    double d = 0;
    for(int i = 0;i < output.size();i++)
        d += pow(output[i]-comp[i],2);
    return sqrt(d);
}
