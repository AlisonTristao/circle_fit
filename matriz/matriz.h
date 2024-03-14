#ifndef MATRIZ
#define MATRIZ
#include "vetor/vetor.h"

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
            arr_data = nullptr;
            col_size = 0;
            row_size = 0;
        }
        virtual ~matriz(){
            delete[] arr_data;
        };

        // manipulação dos dados
        bool verify_dim(const matriz<TYPE>& m) const;
        bool verify_row_col(const matriz<TYPE>& m) const;
        bool verify_row_ele(const vetor<TYPE>& v) const;
        void set_value(int i, int j, TYPE value);
        const TYPE get_value(int i, int j) const;
        // nao implementei pq da mto trabalho
        //matriz<TYPE> stagging();
        //double get_determinant();
        vetor<TYPE> get_row(int index) const;
        vetor<TYPE> get_col(int index) const;
        const int rows() const;
        const int cols() const;
        const string text() const;

        // alltera os operadores
        matriz<TYPE> operator+(const matriz<TYPE>& m);
        matriz<TYPE> operator-(const matriz<TYPE>& m);
        matriz<TYPE> operator*(const matriz<TYPE>& m);
        matriz<TYPE> operator*(const TYPE alfa);
        matriz<TYPE> operator/(const TYPE alfa); // cuidado com matrizes int
        // matriz * vetor coluna
        vetor<TYPE> operator*(const vetor<TYPE>& v); 

        // opradores que nao retornam nada
        void operator=(const matriz<TYPE>& m);
        void operator+=(const matriz<TYPE>& m);
        void operator-=(const matriz<TYPE>& m);
        void operator*=(const TYPE alfa);
        void operator/=(const TYPE alfa); // cuidado com matrizes int
};

// mude acao de erro nessas 5 funcoes seguintes
template <class TYPE>
bool matriz<TYPE>::verify_dim(const matriz<TYPE>& m) const{
    if(this->rows() != m.rows() || this->cols() != m.cols()){
        cout << "Matrizes com dimensoes diferentes" << endl;
        return true;
    }
    return false;
}

template <class TYPE>
bool matriz<TYPE>::verify_row_col(const matriz<TYPE>& m) const{
    if(this->cols() != m.rows()){
        cout << "Matrizes com dimensoes incompativeis para multiplicar" << endl;
        return true;
    }
    return false;
}

template <class TYPE>
bool matriz<TYPE>::verify_row_ele(const vetor<TYPE>& v) const{
    if(this->rows() != v.length()){
        cout << "Matrizes com dimensoes incompativeis com vetor coluna" << endl;
        return true;
    }
    return false;
}


template <class TYPE>
void matriz<TYPE>::set_value(int i, int j, TYPE value){
    if(i >= row_size || i < 0 || j< 0 || j >= col_size){
        cout << "Index inexistente (matriz.set_value)" << endl;
        return;
    }
    arr_data[i].set_value(j, value);
}

template <class TYPE>
const TYPE matriz<TYPE>::get_value(int i, int j) const{
    if(i < 0 || i >= row_size || j < 0 || j >= col_size){
        cout << "Index inexistente (matriz.get_value)" << endl;
        TYPE default_value = 0;
        return default_value;
    }
    return arr_data[i].get_value(j);
}

template <class TYPE>
vetor<TYPE> matriz<TYPE>::get_row(int i) const{
    vetor<TYPE> v(col_size);
    if(i < 0 || i >= row_size) return v;
    for(int j = 0; j < v.length(); j++)
        v.set_value(j, this->get_value(i, j));
    return v;
}

template <class TYPE>
vetor<TYPE> matriz<TYPE>::get_col(int i) const{
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
            result.set_value(i, j, this->get_value(i, j)-m.get_value(i, j));
    return result;
}

template <class TYPE>
matriz<TYPE> matriz<TYPE>::operator*(const TYPE alfa){
    matriz<TYPE> result(this->rows(), this->cols());
    for(int i = 0; i < this->rows(); i++)
        for(int j = 0; j < this->cols(); j++)
            result.set_value(i, j, this->get_value(i, j) * alfa);
    return result;
}

template <class TYPE>
matriz<TYPE> matriz<TYPE>::operator/(const TYPE alfa){
    matriz<TYPE> result(this->rows(), this->cols());
    for(int i = 0; i < this->rows(); i++)
        for(int j = 0; j < this->cols(); j++)
            result.set_value(i, j, this->get_value(i, j)/alfa);
    return result;
}

template <class TYPE>
matriz<TYPE> matriz<TYPE>::operator*(const matriz<TYPE>& m){
    matriz<TYPE> result(this->rows(), m.cols());
    if(this->verify_row_col(m)) result.set_null();
    for(int i = 0; i < result.rows(); i++){
        for(int j = 0; j < result.cols(); j++){
            result.set_value(i, j, this->get_row(i) * m.get_col(j));
        }
    }
    return result;
}

template <class TYPE>
vetor<TYPE> matriz<TYPE>::operator*(const vetor<TYPE>& v){
    vetor<TYPE> result(v.length());
    if(this->verify_row_ele(v)) result.set_null();
    for(int i = 0; i < result.length(); i++){
        result.set_value(i, this->get_row(i) * v);
    }
    return result;
}

template <class TYPE>
void matriz<TYPE>::operator+=(const matriz<TYPE>& m){
    if(this->verify_dim(m)) return;
    for(int i = 0; i < this->rows(); i++)
        for(int j = 0; j < this->cols(); j++)
            this->set_value(i, j, m.get_value(i, j) + this->get_value(i, j));
}

template <class TYPE>
void matriz<TYPE>::operator-=(const matriz<TYPE>& m){
    if(this->verify_dim(m)) return;
    for(int i = 0; i < this->rows(); i++)
        for(int j = 0; j < this->cols(); j++)
            this->set_value(i, j, this->get_value(i, j) - m.get_value(i, j));
}

template <class TYPE>
void matriz<TYPE>::operator*=(const TYPE alfa){
    for(int i = 0; i < this->rows(); i++)
        for(int j = 0; j < this->cols(); j++)
            this->set_value(i, j, this->get_value(i, j) * alfa);
}

template <class TYPE>
void matriz<TYPE>::operator/=(const TYPE alfa){
    for(int i = 0; i < this->rows(); i++)
        for(int j = 0; j < this->cols(); j++)
            this->set_value(i, j, this->get_value(i, j)/alfa);
}

#endif