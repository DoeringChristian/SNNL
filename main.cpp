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
    while(true){
        for(int i = 0;i < 1000;i++){
            n2.update();
            cout << tr.currentNet << "|" << i << "|" << n2.getOutput()[0] << "|" << n2.getOutput()[1] << endl;
        }
        n2 = tr.update(1,0.001);
    }
    return 0;
}
