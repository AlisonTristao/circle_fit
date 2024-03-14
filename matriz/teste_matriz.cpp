#include "matriz.h"
#include "vetor/vetor.h"
#include <iostream>

using namespace std;

int main(){

    int a = 3, b = 3;

    matriz<double> m(a, b);
    matriz<double> v(a, 1);
    matriz<double> g(1, b);

    for(int i = 0; i < a; i++){
        v.set_value(i, 0, i);
        g.set_value(0, i, i);
        for(int j = 0; j < b; j++)
            m.set_value(i, j, i + j);
    }

    matriz<double> result1 = m * v;
    matriz<double> result2 = g * m;

    cout << result1.text() << "\n\n"<< result2.text() << "\n\n"<< g.text() << endl;

    return 0;
}