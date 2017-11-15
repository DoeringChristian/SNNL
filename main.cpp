#include <iostream>
#include "trainer.h"
#include <cstdlib>
#include <math.h>
#include <ctime>

using namespace std;


int main(){
    unsigned int t[3] = {2,3,2};
    Network n(t,3);
    Trainer tr(n,0.01);
    cout << (((double)rand() / (double)(RAND_MAX))*2-1)*0.01 << endl;
    return 0;
}
