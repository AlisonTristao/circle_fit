#ifndef CIRCLEFIT
#define CIRCLEFIT
#include "Matriz/Matriz.h"

#define x 0
#define y 1

// Alison de Oliveira Tristao
// github.com/AlisonTristao

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

        void set_paramns(int len);
        void add_cyclic(TYPE xn, TYPE yn);
        void add_cyclic(Vetor<TYPE>& ponto);
        void linear_system(Matriz<TYPE>& coefficients, Vetor<TYPE>& constants);
        Matriz<TYPE> linear_system();
};

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
    // salva a matriz de pontos
    arr_points.set_value(cyclical_index, x, xn);
    arr_points.set_value(cyclical_index, y, yn);
    // salva os pontos transpostos
    arr_points_transposed.set_value(x, cyclical_index, xn);
    arr_points_transposed.set_value(y, cyclical_index, yn);
    // salva o resultado
    r.set_value(cyclical_index, (xn*xn) + (yn*yn));
    // reseta o index ciclico
    if(++cyclical_index == nPoints) cyclical_index = 0;
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