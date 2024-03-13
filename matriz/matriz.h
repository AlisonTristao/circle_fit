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
        void set_null(){
            col_size = 0;
            row_size = 0;
            arr_data = nullptr;
        }
        virtual ~matriz(){
            delete[] arr_data;
        };

        // manipulação dos dados
        bool verify_dim(const matriz<TYPE>& m2);
        void set_value(int i, int j, TYPE value);
        // nao implementei pq da mto trabalho
        //matriz<TYPE> stagging();
        //double get_determinant();
        const TYPE get_value(int i, int j) const;
        const vetor<TYPE> get_row(int index) const;
        const vetor<TYPE> get_col(int index) const;
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
bool matriz<TYPE>::verify_dim(const matriz<TYPE>& m2){
    if(this->rows() != m2.rows() || this->cols() != m2.cols()){
        cout << "Matrizes com dimensoes diferentes" << endl;
        return true;
    }
    return false;
}

template <class TYPE>
void matriz<TYPE>::set_value(int i, int j, TYPE value){
    if(i >= row_size || i < 0 || j< 0 || j >= col_size){
        cout << "Index inexistente (set_value)" << endl;
        return;
    }
    arr_data[i].set_value(j, value);
}

template <class TYPE>
const TYPE matriz<TYPE>::get_value(int i, int j) const{
    if(i < 0 || i >= row_size || j < 0 || j >= col_size){
        cout << "Index inexistente (get_value)" << endl;
        static TYPE default_value;
        return default_value;
    }
    return arr_data[i].get_value(j);
}

template <class TYPE>
const vetor<TYPE> matriz<TYPE>::get_row(int i) const{
    vetor<TYPE> v(col_size);
    if(i < 0 || i >= row_size) return v;
    for(int j = 0; j < v.length(); j++)
        v.set_value(j, this->get_value(i, j));
    return v;
}

template <class TYPE>
const vetor<TYPE> matriz<TYPE>::get_col(int i) const{
    vetor<TYPE> v(row_size);
    if(i < 0 || i >= col_size) return v;
    for(int j = 0; j < v.length(); j++)
        v.set_value(j, this->get_value(j, i));
    return v;
}

template <class TYPE>
const string matriz<TYPE>::text() const{
    // ex:  [1, 2, 3]
    //      [4, 5, 6]
    //      [7, 8, 9]
    string text;
    for(int i = 0; i < row_size; i++){
        vetor<TYPE> v = this->get_row(i);
        text += v.text();
        if(i < row_size - 1) text += "\n";
    }
    if(row_size == 0 || col_size == 0) text += "[NULL]"; // obj null
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
            this->set_value(i, j, m.get_value(i, j));
}

template <class TYPE>
matriz<TYPE> matriz<TYPE>::operator+(const matriz<TYPE>& m){
    matriz<TYPE> result(this->rows(), this->cols());
    if(this->verify_dim(m)) result.set_null();
    for(int i = 0; i < this->rows(); i++)
        for(int j = 0; j < this->cols(); j++)
            result.set_value(i, j, m.get_value(i, j) + this->get_value(i, j));
    return result;
}

template <class TYPE>
matriz<TYPE> matriz<TYPE>::operator-(const matriz<TYPE>& m){
    matriz<TYPE> result(this->rows(), this->cols());
    if(this->verify_dim(m)) result.set_null();
    for(int i = 0; i < this->rows(); i++)
        for(int j = 0; j < this->cols(); j++)
            result.set_value(i, j, m.get_value(i, j) - this->get_value(i, j));
    return result;
}

#endif