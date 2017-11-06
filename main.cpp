#include <iostream>
#include "vectord.h"

using namespace std;



int main(){
    Vectord v(3);
    v[0] = 1;
    v[1] = 2;
    Vectord v2;
    v2 = sig(v);
    
    return 0;
}
