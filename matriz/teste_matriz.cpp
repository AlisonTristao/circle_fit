#include "matriz.h"
#include "vetor/vetor.h"
#include <iostream>

using namespace std;

int main(){

    int a = 3, b = 3;

    matriz<double> m(a, b);
    vetor<int> v(a);
    vetor<int> g(a);

    for(int i = 0; i < a; i++){
        v.set_value(i, i);
        g.set_value(i, 2*i);
        for(int j = 0; j < b; j++)
            m.set_value(i, j, i + j);
    }

    vetor<int> t = v*2;

    t.set_null();

    m /= 2;

    cout << v.text() << "\n\n"<< m.text() << "\n\n"<< t.text() << endl;

    return 0;
}