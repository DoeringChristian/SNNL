#include "network.h"

Network::Network(){
    this->layers = 0;
    this->m = 0;
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
Network::~Network(){
    delete [] this->m;
    delete [] nodes;
}

void Network::operator =(const Network &n){
    delete [] m;
    delete [] nodes;
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

double Network::fitness(const Vectord &comp) const{
    double d = 0;
    for(int i = 0;i < output.size();i++)
        d += pow(output[i]-comp[i],2);
    return sqrt(d);
}

bool Network::SavetoFile(const string file) const{
    ofstream out;
    out.open(file);
    out << (char)this->size();
    for(int i = 0;i < size();i++)
        out << (char)sizeAt(i);
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
    in.get(c);
    layers = c;
    this->nodes = new unsigned int[layers];
    for(int i = 0;i < layers;i++){
        in.get(c);
        nodes[i] = (unsigned int)c;
    }
    this->input = Vectord(nodes[0]);
    this->output = Vectord(nodes[layers-1]);
    this->m = new Matrixd[layers-1];
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

















