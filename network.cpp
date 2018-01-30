#include "network.h"

Network::Network(){
    this->layers = 0;
    this->weights = 0;
    this->nodes = 0;
    this->bias = 0;
    fitness = 0;
    structure = 0;
    has_bias = true;
}
Network::Network(unsigned int structure[], unsigned int layers, bool has_bias){
    this->layers = layers;
    this->structure = new unsigned int[layers];
    for(uint i = 0;i < layers;i++)
        this->structure[i] = structure[i];
    this->nodes = new Vectord[layers];
    this->weights = new Matrixd[layers-1];
    this->bias = new Vectord[layers-1];
    for(uint i = 0;i < layers-1;i++)
        weights[i] = Matrixd(structure[i],structure[i+1]);
    for(uint i = 0;i < layers;i++)
        nodes[i] = Vectord(structure[i]);
    if(has_bias)
        for(uint i = 0;i < layers-1;i++)
            bias[i] = Vectord(structure[i+1]);
    else 
        bias = 0;
    this->has_bias = has_bias;
}
Network::Network(const Network &copy){
    fitness = copy.getFitness();
    this->structure = new unsigned int[copy.size()];
    for(uint i = 0;i < copy.size();i++)
        this->structure[i] = copy.sizeAt(i);
    this->layers = copy.size();
    this->nodes = new Vectord[copy.size()];
    this->weights = new Matrixd[copy.size()-1];
    for(uint i = 0;i < layers-1;i++)
        weights[i] = copy[i];
    for(uint i = 0;i < layers;i++)
        nodes[i] = copy(i);
    if(copy.has_bias){
        this->bias = new Vectord[copy.size()-1];
        for(uint i = 0;i < layers-1;i++)
            bias[i] = copy.bias[i];
        this->has_bias = true;
    }
    else{
        uint max_size = 0;
        for(uint i = 0;i < layers-1;i++)
            if(this->structure[i+1] > max_size)
                max_size = structure[i+1];
        this->bias = new Vectord(max_size);
        this->has_bias = false;
    }
        
}

Network::~Network(){
    delete [] this->weights;
    delete [] this->nodes;
    if(has_bias)
        delete [] this->bias;
    delete [] structure;
}

void Network::operator =(const Network &copy){
    delete [] weights;
    delete [] structure;
    delete [] nodes;
    if(this->has_bias)
        delete [] bias;
    fitness = copy.getFitness();
    this->structure = new unsigned int[copy.size()];
    for(uint i = 0;i < copy.size();i++)
        this->structure[i] = copy.sizeAt(i);
    this->layers = copy.size();
    this->nodes = new Vectord[copy.size()];
    this->weights = new Matrixd[copy.size()-1];
    this->bias = new Vectord[copy.size()-1];
    for(uint i = 0;i < layers-1;i++)
        weights[i] = copy[i];
    for(uint i = 0;i < layers;i++)
        nodes[i] = copy(i);
    if(copy.has_bias){
        this->bias = new Vectord[copy.size()-1];
        for(uint i = 0;i < layers-1;i++)
            bias[i] = copy.bias[i];
        this->has_bias = true;
    }
    else{
        uint max_size = 0;
        for(uint i = 0;i < layers-1;i++)
            if(this->structure[i+1] > max_size)
                max_size = structure[i+1];
        this->bias = new Vectord(max_size);
        this->has_bias = false;
    }
}

bool Network::operator +=(const Network &partner){
    if(size() != partner.size())
        return false;
    for(uint i = 0;i < size();i++)
        if(this->sizeAt(i) != partner.sizeAt(i))
            return false;
    
    for(uint i = 0;i < this->size()-1;i++)
        for(uint j = 0;j < this->weights[i].getWidth();j++)
            for(uint k = 0;k < this->weights[i].getHeight();k++)
                if((int)rand() % 2 == 0)
                    this->weights[i][j][k] = partner[i][j][k];
    if(this->has_bias)
        for(uint i = 0;i < this->size()-1;i++)
            for(uint j = 0;j < this->bias[i].size();j++)
                if((int)rand() % 2 == 0)
                    this->bias[i][j] = partner.bias[i][j];
    return true;
}

Matrixd &Network::operator[](unsigned int index) const{
    return weights[index];
}

Vectord &Network::operator ()(unsigned int index) const{
    return nodes[index];
}

void Network::update(){
    for(uint i = 0;i < layers-1;i++){
        if(this->has_bias)
            this->nodes[i+1] = sig(this->nodes[i]*weights[i]+bias[i]);
        else
            this->nodes[i+1] = sig(this->nodes[i]*weights[i]);
    }
        
}

unsigned int Network::size() const{
    return layers;
}

Vectord Network::getOutput() const{
    return this->nodes[layers-1];
}

void Network::setInput(unsigned int index,double value){
    if(index < structure[0])
        this->nodes[0][index] = value;
}

unsigned int Network::sizeAt(unsigned int index) const{
    return structure[index];
}

bool Network::SavetoFile(const string file) const{
    ofstream out;
    out.open(file.c_str());
    out << this->layers << endl;
    for(uint i = 0;i < this->size();i++)
        out << this->structure[i] << endl;
    for(uint i = 0;i < this->size()-1;i++)
        for(uint j = 0;j < this->weights[i].getWidth();j++)
            for(uint k = 0;k < this->weights[i].getHeight();k++)
                out << this->weights[i][j][k] << endl;
    if(this->has_bias)
        for(uint i = 0;i < this->size()-1;i++)
            for(uint j = 0;j < this->bias[i].size();j++)
                out << this->bias[i][j] << endl;
    out.close();
    return true;
}

bool Network::LoadFile(const string file){
    ifstream in(file.c_str());
    if(in.good()){
	    //delete old:
	    delete [] this->weights;
	    delete [] structure;
        delete [] this->nodes;
        delete [] bias;
	    //make new:
	    string line;
        getline(in,line);
        layers = atoi(line.c_str());
        structure = new uint[layers];
        for(uint i = 0;i < this->layers;i++){
            getline(in,line);
            structure[i] = atoi(line.c_str());
        }
        
        bias = new Vectord[this->layers-1];
        weights = new Matrixd[this->layers-1];
        nodes = new Vectord[this->layers];
        
        for(uint i = 0;i < this->layers;i++)
            nodes[i] = Vectord(structure[i]);
        
        for(uint i = 0;i < size()-1;i++){
            weights[i] = Matrixd(this->structure[i],this->structure[i+1]);
            for(uint j = 0;j < this->structure[i];j++)
                for(uint k = 0;k < this->structure[i+1];k++){
                    getline(in,line);
                    weights[i][j][k] = atof(line.c_str());
                }
        }
        if(this->has_bias)
            for(uint i = 0;i < this->size()-1;i++){
                bias[i] = Vectord(structure[i+1]);
                for(uint j = 0;j < this->structure[i+1];j++){
                bias[i][j] = atof(line.c_str());
                }
            }
        
	    return true;
	}
	else
        return false;
    in.close();
    return true;
}

double Network::getFitness() const{
    return fitness;
}

void Network::setFitness(double fitness){
    this->fitness = fitness;
}

void Network::randomize(double randomness,double shift){
    for(uint i = 0;i < this->size()-1;i++)
        for(uint j = 0;j < weights[i].getWidth();j++)
            for(uint k = 0;k < weights[i].getHeight();k++)
                if(rand()/(RAND_MAX+1.0) < randomness)
                    weights[i][j][k] += (((double)rand() / (double)(RAND_MAX))*2-1)*shift;
    if(has_bias)
        for(uint i = 0;i < layers-1;i++)
            for(uint j = 0;j < this->bias[i].size();j++)
                if(rand()/(RAND_MAX+1.0) < randomness)
                    bias[i][j] += (((double)rand() / (double)(RAND_MAX))*2-1)*shift;
            
}


Vectord &Network::getbias(unsigned int index) const{
    if(has_bias)
        return bias[index];
    else
        return *bias;
}













