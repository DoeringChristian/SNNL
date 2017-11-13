#include <iostream>
#include "network.h"
#include <cstdlib>
#include <math.h>
#include <ctime>

using namespace std;


int main(){
    srand(10);
    unsigned int i[3] = {2,3,2};
    Vectord out(2);
    out[0] = 0.5;
    out[1] = 0.5;
    Network n(i,3);
    n.setInput(0,1);
    n.setInput(1,1);
    
    Network n2;
    n2 = n;
    int c = 0;
    n[0][0][0] = 0.0145;
    n.SavetoFile("test.txt");
    n2.LoadFile("test.txt");
    cout << n2[0][0][0] << endl;
    
    return 0;
}
