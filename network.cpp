#include "network.h"

Network::Network(){
    this->layers = 0;
    this->m = 0;
    fitness = 0;
    nodes = 0;
}
Network::Network(unsigned int nodes[],unsigned int layers){
    this->layers = layers;
    this->nodes = new unsigned int[layers];
    for(int i = 0;i < layers;i++)
        this->nodes[i] = nodes[i];
    this->input = Vectord(nodes[0]);
    this->output = Vectord(nodes[layers-1]);
    this->m = new Matrixd[layers-1];
    for(int i = 0;i < layers-1;i++)
        m[i] = Matrixd(nodes[i],nodes[i+1]);
}
Network::Network(const Network &copy){
    fitness = copy.getFitness();
    this->nodes = new unsigned int[copy.size()];
    for(int i = 0;i < copy.size();i++)
        this->nodes[i] = copy.sizeAt(i);
    this->layers = copy.size();
    this->input = copy.input;
    this->output = copy.output;
    this->m = new Matrixd[copy.size()-1];
    for(int i = 0;i < layers-1;i++)
        m[i] = copy[i];
}

Network::~Network(){
    delete [] this->m;
    delete [] nodes;
}

void Network::operator =(const Network &n){
    delete [] m;
    delete [] nodes;
    fitness = n.getFitness();
    this->nodes = new unsigned int[n.size()];
    for(int i = 0;i < n.size();i++)
        this->nodes[i] = n.sizeAt(i);
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
    return nodes[index];
}

bool Network::SavetoFile(const string file) const{
    ofstream out;
    out.open(file);
    //output size of network
    for(int i = 0;i < 4;i++)
        out << ((char*)&layers)[i];
    //output size of vectors
    for(int i = 0;i < size();i++)
        for(int j = 0;j < 4;j++)
            out << ((char*)&nodes[i])[j];
    //output matrices
    for(int i = 0;i < size()-1;i++)
        for(int j = 0;j < m[i].getHeight();j++){
            for(int k = 0;k < m[i].getWidth();k++)
                for(int l = 0;l < 8;l++)
                    out << ((char*)&m[i][k][j])[l];
        }
    out.close();
    return true;
}

bool Network::LoadFile(const string file){
    ifstream in;
    in.open(file);
    //delete old:
    delete [] this->m;
    delete [] nodes;
    //make new:
    char c;
    //set length/layers
    for(int i = 0;i < 4;i++){
        in.get(c);
        ((char*)&layers)[i] = c;
    }
    //set length of matrices
    this->nodes = new unsigned int[layers];
    for(int i = 0;i < layers;i++){
        for(int j = 0;j < 4;j++){
            in.get(c);
            ((char*)&nodes[i])[j] = c;
        }
    }
    //init input & output vector according to their saved length
    this->input = Vectord(nodes[0]);
    this->output = Vectord(nodes[layers-1]);
    this->m = new Matrixd[layers-1];
    //setting the values of the matrecis
    for(int i = 0;i < layers-1;i++){
        m[i] = Matrixd(nodes[i],nodes[i+1]);
        for(int j = 0;j < m[i].getHeight();j++)
            for(int k = 0;k < m[i].getWidth();k++)
                for(int l = 0;l < 8;l++){
                    in.get(c);
                    ((char*)&m[i][k][j])[l] = c;
                }
                    
    }
    return true;
}

double Network::getFitness() const{
    return fitness;
}

void Network::setFitness(double fitness){
    this->fitness = fitness;
}















