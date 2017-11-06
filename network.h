#ifndef NETWORK_H
#define NETWORK_H
#include "matrixd.h"

struct Network{
    //variables
    unsigned int layers;
    unsigned int *nodes;
    Vectord *v;
    Matrixd *m;
    //con-/destructors
    Network();
    Network(unsigned int nodes[]);
    ~Network();
};

#endif // NETWORK_H
