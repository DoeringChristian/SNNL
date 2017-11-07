#include <iostream>
#include "network.h"
#include "m.h"

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
    while(true){
        srand(time(0));
        for(int i = 0;i < n.size()-1;i++)
            for(int j = 0;j < n[i].getWidth();j++)
                for(int k = 0;k < n[i].getHeight();k++)
                    n[i][j][k] += ((((double) rand()/RAND_MAX)*2)-1)/1000;
        n2.update();
        n.update();
        if(n.fitness(out) < n2.fitness(out)){
            if(c > 1)
                cout << "######################################################################" << endl;
            cout << "________________________________________________________________" << endl;
            cout << "fitness:n,n2:" << n.fitness(out) << "|" << n2.fitness(out) << endl;
            cout << "output  n:" << n.getOutput()[0] << "|" << n.getOutput()[1] << endl;
            cout << "output n2:" << n2.getOutput()[0] << "|" << n2.getOutput()[1] << endl;
            cout << "unsuccessful mutations:" << c << endl;
            cout << "________________________________________________________________" << endl;
            c = 0;
            n2 = n;
        }
        else if(n.fitness(out) == 0){
            n2 = n;
            cout << "________________________________________________________________" << endl;
            cout << "fitness:n,n2:" << n.fitness(out) << "|" << n2.fitness(out) << endl;
            cout << "output  n:" << n.getOutput()[0] << "|" << n.getOutput()[1] << endl;
            cout << "output n2:" << n2.getOutput()[0] << "|" << n2.getOutput()[1] << endl;
            cout << "________________________________________________________________" << endl;
            c = 0;
            break;
        }
        else{
            n = n2;
            c++;
        }
            //cout << "#" << endl;
    }
    
    
    return 0;
}
