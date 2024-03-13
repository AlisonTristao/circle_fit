#include "matriz.h"
#include "vetor/vetor.h"
#include <iostream>

using namespace std;

int main(){

    int a = 2, b = 3;

    matriz<int> m(a, b);

    for(int i = 0; i < a; i++)
        for(int j = 0; j < b; j++)
            m.set_value(i, j, i + j);

    matriz<int> v(b, a);

    for(int i = 0; i < b; i++)
        for(int j = 0; j < a; j++)
            v.set_value(i, j, i + j);

    matriz<int> t = m + v;

    cout << v.text() << "\n\n"<< m.text() << "\n\n"<< t.text() << endl;

    return 0;
}