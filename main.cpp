#include <iostream>
#include "network.h"
#include <cstdlib>
#include <math.h>
#include <ctime>

using namespace std;


int main(){
    unsigned int t[3] = {2,3,2};
    Network n(t,3);
    Trainer tr(n,0.01);
    Network n2;
    n2 = tr.update(1,0.001);
    n2.setInput(1,10);
    for(int i = 0;i < 100;i++){
        for(int j = 0;j < 100;j++){
            n.setInput(i,j);
            n.update();
            cout << n.getOutput()[0] << "|" << n.getOutput()[1] << endl;
        }
    }
    return 0;
}
