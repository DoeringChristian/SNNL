#include "network.h"

Network::Network(){
    this->layers = 0;
    this->m = 0;
    this->v = 0;
    this->bias = 0;
    fitness = 0;
    nodes = 0;
}
Network::Network(unsigned int nodes[],unsigned int layers){
    this->layers = layers;
    this->nodes = new unsigned int[layers];
    for(uint i = 0;i < layers;i++)
        this->nodes[i] = nodes[i];
    this->v = new Vectord[layers];
    this->m = new Matrixd[layers-1];
    this->bias = new Vectord[layers-1];
    for(uint i = 0;i < layers-1;i++)
        m[i] = Matrixd(nodes[i],nodes[i+1]);
    for(uint i = 0;i < layers;i++)
        v[i] = Vectord(nodes[i]);
    for(uint i = 0;i < layers-1;i++)
        bias[i] = Vectord(nodes[i+1]);
}
Network::Network(const Network &copy){
    fitness = copy.getFitness();
    this->nodes = new unsigned int[copy.size()];
    for(uint i = 0;i < copy.size();i++)
        this->nodes[i] = copy.sizeAt(i);
    this->layers = copy.size();
    this->v = new Vectord[copy.size()];
    this->m = new Matrixd[copy.size()-1];
    this->bias = new Vectord[copy.size()-1];
    for(uint i = 0;i < layers-1;i++)
        m[i] = copy[i];
    for(uint i = 0;i < layers;i++)
        v[i] = copy(i);
    for(uint i = 0;i < layers-1;i++)
        bias[i] = copy.bias[i];
}

Network::~Network(){
    delete [] this->m;
    delete [] this->v;
    delete [] this->bias;
    delete [] nodes;
}

void Network::operator =(const Network &n){
    delete [] m;
    delete [] nodes;
    delete [] v;
    delete [] bias;
    fitness = n.getFitness();
    this->nodes = new unsigned int[n.size()];
    for(uint i = 0;i < n.size();i++)
        this->nodes[i] = n.sizeAt(i);
    this->layers = n.size();
    this->v = new Vectord[n.size()];
    this->m = new Matrixd[n.size()-1];
    this->bias = new Vectord[n.size()-1];
    for(uint i = 0;i < layers-1;i++)
        m[i] = n[i];
    for(uint i = 0;i < layers;i++)
        v[i] = n(i);
    for(uint i = 0;i < layers-1;i++)
        bias[i] = n.bias[i];
}

bool Network::operator +=(const Network &partner){
    if(size() != partner.size())
        return false;
    for(uint i = 0;i < size();i++)
        if(this->sizeAt(i) != partner.sizeAt(i))
            return false;
    
    for(uint i = 0;i < this->size()-1;i++)
        for(uint j = 0;j < this->m[i].getWidth();j++)
            for(uint k = 0;k < this->m[i].getHeight();k++)
                if((int)rand() % 2 == 0)
                    this->m[i][j][k] = partner[i][j][k];
    for(uint i = 0;i < this->size()-1;i++)
        for(uint j = 0;j < this->bias[i].size();j++)
            if((int)rand() % 2 == 0)
                this->bias[i][j] = partner.bias[i][j];
    return true;
}

Matrixd &Network::operator[](unsigned int index) const{
    return m[index];
}

Vectord &Network::operator ()(unsigned int index) const{
    return v[index];
}

void Network::update(){
    for(uint i = 0;i < layers-1;i++)
        this->v[i+1] = sig(this->v[i]*m[i]+bias[i]);
        
}

unsigned int Network::size() const{
    return layers;
}

Vectord Network::getOutput() const{
    return this->v[layers-1];
}

void Network::setInput(unsigned int index,double value){
    if(index < nodes[0])
        this->v[0][index] = value;
}

unsigned int Network::sizeAt(unsigned int index) const{
    return nodes[index];
}

bool Network::SavetoFile(const string file) const{
    ofstream out;
    out.open(file.c_str());
    //output size of network
    for(int i = 0;i < 4;i++)
        out << ((char*)&layers)[i];
    //output size of vectors
    for(uint i = 0;i < size();i++)
        for(int j = 0;j < 4;j++)
            out << ((char*)&nodes[i])[j];
    //output matrices
    for(uint i = 0;i < size()-1;i++)
        for(uint j = 0;j < m[i].getHeight();j++)
            for(uint k = 0;k < m[i].getWidth();k++)
                for(uint l = 0;l < 8;l++)
                    out << ((char*)&m[i][k][j])[l];
    //output bias
    for(uint i = 0;i < size()-1;i++)
        for(uint j = 0;j < nodes[i];j++)
            for(uint k = 0;k < 8;k++)
                out << ((char*)&bias[i][j])[k];
    out.close();
    return true;
}

bool Network::LoadFile(const string file){
    ifstream in(file.c_str());
    if(in.good()){
	    //delete old:
	    delete [] this->m;
	    delete [] nodes;
        delete [] bias;
	    //make new:
	    char c;
	    //set length/layers
	    for(int i = 0;i < 4;i++){
	        in.get(c);
	        ((char*)&layers)[i] = c;
	    }
	    //set length of matrices
	    this->nodes = new unsigned int[layers];
	    for(uint i = 0;i < layers;i++){
	        for(uint j = 0;j < 4;j++){
	            in.get(c);
	            ((char*)&nodes[i])[j] = c;
	        }
	    }
	    //init vector array according to it's lengths
	    for(uint i = 0;i < layers;i++)
	        v[i] = Vectord(nodes[i]);
	    this->m = new Matrixd[layers-1];
	    //setting the values of the matrecis
	    for(uint i = 0;i < layers-1;i++){
	        m[i] = Matrixd(nodes[i],nodes[i+1]);
	        for(uint j = 0;j < m[i].getHeight();j++)
                for(uint k = 0;k < m[i].getWidth();k++)
                    for(uint l = 0;l < 8;l++){
	                    in.get(c);
	                    ((char*)&m[i][k][j])[l] = c;
                    }      
	    }
        //input bias
        this->bias = new Vectord[size()-1];
        for(uint i = 0;i < size()-1;i++){
            bias[i] = Vectord(nodes[i+1]);
            for(uint j = 0;j < nodes[i+1];j++)
                for(uint k = 0;k < 8;k++){
                    in.get(c);
                    ((char*)&bias[i][j])[k] = c;
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
        for(uint j = 0;j < m[i].getWidth();j++)
            for(uint k = 0;k < m[i].getHeight();k++)
                if(rand()/(RAND_MAX+1.0) < randomness)
                    m[i][j][k] += (((double)rand() / (double)(RAND_MAX))*2-1)*shift;
    for(uint i = 0;i < layers-1;i++)
        for(uint j = 0;j < this->bias[i].size();j++)
            if(rand()/(RAND_MAX+1.0) < randomness)
                bias[i][j] += (((double)rand() / (double)(RAND_MAX))*2-1)*shift;
}


Vectord &Network::getbias(unsigned int index) const{
    return bias[index];
}













