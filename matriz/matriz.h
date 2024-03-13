#ifndef MATRIZ
#define MATRIZ
#include "vetor/vetor.h"
#include <string>
#include <cmath>
#include <iostream>

using namespace std;

// Alison de Oliveira Tristao
// github.com/AlisonTristao

// *******************************
// *       Class of Matrix       *
// *******************************

/*
    CUIDADO NA INTERAÇÂO DE MATRIZES DE TAMANHOS DIFERENTES
    ao acessar itens fora do tamanho da matriz, as funções retornam zero

    ex multiplicação:
    (ele vai completar a linha que falta com zeros)

    [1, 2, 4]       [1, 2, 3]
    [3, 4, 5]   *   [3, 4, 5]
    [6, 7, 8]       [0, 0, 0] <-
*/

template <class TYPE>
class matriz {
    private:
        int row_size,  col_size;
        vetor<TYPE>* arr_data;
    public:
        matriz(int row, int col) : row_size(row), col_size(col){
            arr_data = new vetor<TYPE>[row];
            for(int j = 0; j < row; j++)
                arr_data[j].set_size(col);
        };
        virtual ~matriz(){
            delete[] arr_data;
        };

        // manipulação dos dados
        void set_value(int i, int j, TYPE value);
        // nao implementei pq da mto trabalho
        //matriz<TYPE> stagging();
        //double get_determinant();
        const TYPE get_value(int i, int j) const;
        vetor<TYPE> get_row(int index);
        vetor<TYPE> get_col(int index);
        const int rows() const;
        const int cols() const;
        const string text() const;

        // alltera os operadores
        matriz<TYPE> operator+(const matriz<TYPE>& v);
        matriz<TYPE> operator-(const matriz<TYPE>& v);
        matriz<TYPE> operator*(const vetor<TYPE> alfa) const;
        matriz<TYPE> operator*(const TYPE alfa) const;
        matriz<TYPE> operator/(const TYPE alfa) const; // cuidado com vetores int
        // vetor linha * vetor coluna
        TYPE operator*(const vetor<TYPE>& v);

        // opradores que nao retornam nada
        void operator=(const matriz<TYPE>& m);
        void operator+=(const matriz<TYPE>& m);
        void operator-=(const matriz<TYPE>& m);
        void operator*=(const TYPE alfa);
        void operator/=(const TYPE alfa); // cuidado com vetores int
};

template <class TYPE>
void matriz<TYPE>::set_value(int i, int j, TYPE value){
    if(i >= row_size || i < 0 || j< 0 || j >= col_size) return;
    arr_data[i].set_value(j, value);
}

template <class TYPE>
const TYPE matriz<TYPE>::get_value(int i, int j) const{
    if(i < 0 || i >= row_size || j < 0 || j >= col_size){
        static TYPE default_value;
        return default_value;
    }
    return arr_data[i].get_value(j);
}

template <class TYPE>
vetor<TYPE> matriz<TYPE>::get_row(int i){
    vetor<TYPE> v(col_size);
    if(i < 0 || i >= row_size) return v;
    for(int j = 0; j < v.length(); j++)
        v.set_value(j, arr_data[i].get_value(j));
    return v;
}

template <class TYPE>
vetor<TYPE> matriz<TYPE>::get_col(int i){
    vetor<TYPE> v(row_size);
    if(i < 0 || i >= col_size) return v;
    for(int j = 0; j < v.length(); j++)
        v.set_value(j, arr_data[j].get_value(i));
    return v;
}

template <class TYPE>
const string matriz<TYPE>::text() const{
    // ex:  [1, 2, 3]
    //      [4, 5, 6]
    //      [7, 8, 9]
    string text;
    for(int i = 0; i < row_size; i++){
        text += arr_data[i].text();
        if(i < row_size - 1) text += "\n";
    }
    return text; 
}

template <class TYPE>
const int matriz<TYPE>::cols() const{
    return col_size; 
}

template <class TYPE>
const int matriz<TYPE>::rows() const{
    return row_size; 
}

// cuidado com matriz definidos com tamanho diferentes
template <class TYPE>
void matriz<TYPE>::operator=(const matriz<TYPE>& m){
    for(int i = 0; i < row_size; i++)
        for(int j = 0; j < col_size; j++)
            arr_data[i].set_value(j, 2);
}

template <class TYPE>
matriz<TYPE> matriz<TYPE>::operator+(const matriz<TYPE>& m){
    // maior comprimento de cada
    int max_rows = (m.rows() > this->rows()) ? m.rows() : this->rows();
    int max_cols = (m.cols() > this->cols()) ? m.cols() : this->cols();
    // completa os numeros vazios com 0
    matriz<TYPE> result(max_rows, max_cols);
    for(int i = 0; i < max_rows; i++)
        for(int j = 0; j < max_cols; j++)
            result.set_value(i, j, m.get_value(i, j) + this->get_value(i, j));
    return result;
}



#endif