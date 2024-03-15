#ifndef CIRCLEFIT
#define CIRCLEFIT
#include "Matriz/Matriz.h"

#define x 0
#define y 1

// Alison de Oliveira Tristao
// github.com/AlisonTristao

/*
    Usamos a equação do circulo:
    (x + x0)² + (y + y0)² = R²
                ||
                \/

    2x0 x + 2y0 y + (x0² + y0² -R²) = x²+y²
    a x   + b y   + c               = x²+y²

    logo, para N pontos:

    [x1 y1 1] * [a] = [x1²+y1²]
       ...      [b]      ...
    [xn yn 1]   [c]   [xn²+yn²]

    solucionando esses sistema super determinado, 
    achamos o raio e o centro deslocado
*/

// **********************************
// *       Class of CircleFit       *
// **********************************

template <class TYPE>
class CircleFit {
    private:
        int nPoints = 0, cyclical_index = 0;
        Matriz<TYPE> arr_points, arr_points_transposed;
        Vetor<TYPE> r;
    public:
        CircleFit(int len){
            arr_points.set_size(len, 3);
            set_paramns(len);
        };
        virtual ~CircleFit(){};

        const string text() const;
        void set_paramns(int len);
        void set_value(int index, TYPE xn, TYPE yn);
        void add_cyclic(TYPE xn, TYPE yn);
        void add_cyclic(Vetor<TYPE>& ponto);
        void linear_system(Matriz<TYPE>& coefficients, Vetor<TYPE>& constants);
        Matriz<TYPE> linear_system();
};

template <class TYPE>
const string CircleFit<TYPE>::text() const{
    string text = "Pontos: \n[x, y]\n";
    for(int i  = 0; i < nPoints; i++){
        text += "[";
        text += to_string(arr_points.get_value(i, 0));
        text += ", ";
        text += to_string(arr_points.get_value(i, 1));
        text += "]\n";
    }
    return text;
}

template <class TYPE>
void CircleFit<TYPE>::set_paramns(int len){
    nPoints = len;
    // montam o sistema derivado do sistema
    // (At * A) b = At * r          A = arr_points
    // com b sendo a solução do sistema 
    arr_points_transposed.set_size(3, len);
    r.set_size(len);

    // a coluna 1 de A e e a linha 1 de At sao 1
    for(int i = 0; i < len; i++){
        arr_points.set_value(i, 2, 1);
        arr_points_transposed.set_value(2, i, 1);
    }
}

template <class TYPE>
void CircleFit<TYPE>::add_cyclic(TYPE xn, TYPE yn){
    this->set_value(cyclical_index, xn, yn);
    // reseta o index ciclico
    if(++cyclical_index == nPoints) cyclical_index = 0;
}

template <class TYPE>
void CircleFit<TYPE>::set_value(int index, TYPE xn, TYPE yn){
    // salva a matriz de pontos
    arr_points.set_value(index, x, xn);
    arr_points.set_value(index, y, yn);
    // salva os pontos transpostos
    arr_points_transposed.set_value(x, index, xn);
    arr_points_transposed.set_value(y, index, yn);
    // salva o resultado
    r.set_value(index, (xn*xn) + (yn*yn));
}

template <class TYPE>
void CircleFit<TYPE>::add_cyclic(Vetor<TYPE>& ponto){
    add_cyclic(ponto.get_value(x), ponto.get_value(y));
} 

template <class TYPE>
void CircleFit<TYPE>::linear_system(Matriz<TYPE>& coefficients, Vetor<TYPE>& constants){
    coefficients = arr_points_transposed * arr_points;
    constants = arr_points_transposed * r;
}

template <class TYPE>
Matriz<TYPE> CircleFit<TYPE>::linear_system(){
    Matriz<TYPE> system(3, 4);
    Matriz<TYPE> coefficients = arr_points_transposed * arr_points;
    Vetor<TYPE> constants = arr_points_transposed * r;
    for(int i = 0; i < 3; i++){
        system.set_value(i, 0, coefficients.get_value(i, 0));
        system.set_value(i, 1, coefficients.get_value(i, 1));
        system.set_value(i, 2, coefficients.get_value(i, 2));
        system.set_value(i, 3, constants.get_value(i));
    }
    return system;
}

#endif