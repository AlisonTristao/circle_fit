#ifndef MATRIZ
#define MATRIZ
#include "Vetor/Vetor.h"

// Alison de Oliveira Tristao
// github.com/AlisonTristao

// *******************************
// *       Class of Matrix       *
// *******************************

template <class TYPE>
class Matriz {
    private:
        int row_size = 0,  col_size = 0;
        Vetor<TYPE>* arr_data;
    public:
        Matriz(){}; // default constructor
        Matriz(int row, int col){
            set_size(row, col);
        };
        void set_size(int row, int col){
            col_size = col;
            row_size = row;
            arr_data = new Vetor<TYPE>[row];
            for(int j = 0; j < row; j++)
                arr_data[j].set_size(col);
        }
        void set_null(){
            arr_data = nullptr;
            col_size = 0;
            row_size = 0;
        }
        virtual ~Matriz(){
            delete[] arr_data;
        };

        // manipulação dos dados
        bool verify_dim(const Matriz<TYPE>& m) const;
        bool verify_row_col(const Matriz<TYPE>& m) const;
        bool verify_row_ele(const Vetor<TYPE>& v) const;
        void set_value(int i, int j, TYPE value);
        const TYPE get_value(int i, int j) const;
        // nao implementei pq da mto trabalho
        //Matriz<TYPE> stagging();
        //double get_determinant();
        Vetor<TYPE> get_row(int index) const;
        Vetor<TYPE> get_col(int index) const;
        int rows() const;
        int cols() const;
        const string text() const;

        // alltera os operadores
        Matriz<TYPE> operator+(const Matriz<TYPE>& m);
        Matriz<TYPE> operator-(const Matriz<TYPE>& m);
        Matriz<TYPE> operator*(const Matriz<TYPE>& m);
        Matriz<TYPE> operator*(const TYPE alfa);
        Matriz<TYPE> operator/(const TYPE alfa); // cuidado com Matrizes int
        // Matriz * Vetor coluna
        Vetor<TYPE> operator*(const Vetor<TYPE>& v); 

        // opradores que nao retornam nada
        void operator=(const Matriz<TYPE>& m);
        void operator+=(const Matriz<TYPE>& m);
        void operator-=(const Matriz<TYPE>& m);
        void operator*=(const TYPE alfa);
        void operator/=(const TYPE alfa); // cuidado com Matrizes int
};

// mude acao de erro nessas 5 funcoes seguintes
template <class TYPE>
bool Matriz<TYPE>::verify_dim(const Matriz<TYPE>& m) const{
    if(this->rows() != m.rows() || this->cols() != m.cols()){
        cout << "Matrizes com dimensoes diferentes" << endl;
        return true;
    }
    return false;
}

template <class TYPE>
bool Matriz<TYPE>::verify_row_col(const Matriz<TYPE>& m) const{
    if(this->cols() != m.rows()){
        cout << "Matrizes com dimensoes incompativeis para multiplicar" << endl;
        return true;
    }
    return false;
}

template <class TYPE>
bool Matriz<TYPE>::verify_row_ele(const Vetor<TYPE>& v) const{
    if(this->cols() != v.length()){
        cout << "Matrizes com dimensoes incompativeis com Vetor coluna" << endl;
        return true;
    }
    return false;
}


template <class TYPE>
void Matriz<TYPE>::set_value(int i, int j, TYPE value){
    if(i >= row_size || i < 0 || j< 0 || j >= col_size){
        cout << "Index inexistente (Matriz.set_value)" << endl;
        return;
    }
    arr_data[i].set_value(j, value);
}

template <class TYPE>
const TYPE Matriz<TYPE>::get_value(int i, int j) const{
    if(i < 0 || i >= row_size || j < 0 || j >= col_size){
        cout << "Index inexistente (Matriz.get_value)" << endl;
        TYPE default_value = 0;
        return default_value;
    }
    return arr_data[i].get_value(j);
}

template <class TYPE>
Vetor<TYPE> Matriz<TYPE>::get_row(int i) const{
    Vetor<TYPE> v(col_size);
    if(i < 0 || i >= row_size) return v;
    for(int j = 0; j < v.length(); j++)
        v.set_value(j, this->get_value(i, j));
    return v;
}

template <class TYPE>
Vetor<TYPE> Matriz<TYPE>::get_col(int i) const{
    Vetor<TYPE> v(row_size);
    if(i < 0 || i >= col_size) return v;
    for(int j = 0; j < v.length(); j++)
        v.set_value(j, this->get_value(j, i));
    return v;
}

template <class TYPE>
const string Matriz<TYPE>::text() const{
    // ex:  [1, 2, 3]
    //      [4, 5, 6]
    //      [7, 8, 9]
    string text;
    for(int i = 0; i < row_size; i++){
        Vetor<TYPE> v = this->get_row(i);
        text += v.text();
        text += "\n";
    }
    if(row_size == 0 || col_size == 0) text += "[NULL]\n"; // obj null
    return text; 
}

template <class TYPE>
int Matriz<TYPE>::cols() const{
    return col_size; 
}

template <class TYPE>
int Matriz<TYPE>::rows() const{
    return row_size; 
}

// cuidado com Matriz definidos com tamanho diferentes
template <class TYPE>
void Matriz<TYPE>::operator=(const Matriz<TYPE>& m){
    for(int i = 0; i < row_size; i++)
        for(int j = 0; j < col_size; j++)
            this->set_value(i, j, m.get_value(i, j));
}

template <class TYPE>
Matriz<TYPE> Matriz<TYPE>::operator+(const Matriz<TYPE>& m){
    Matriz<TYPE> result(this->rows(), this->cols());
    if(this->verify_dim(m)) result.set_null();
    for(int i = 0; i < this->rows(); i++)
        for(int j = 0; j < this->cols(); j++)
            result.set_value(i, j, m.get_value(i, j) + this->get_value(i, j));
    return result;
}

template <class TYPE>
Matriz<TYPE> Matriz<TYPE>::operator-(const Matriz<TYPE>& m){
    Matriz<TYPE> result(this->rows(), this->cols());
    if(this->verify_dim(m)) result.set_null();
    for(int i = 0; i < this->rows(); i++)
        for(int j = 0; j < this->cols(); j++)
            result.set_value(i, j, this->get_value(i, j)-m.get_value(i, j));
    return result;
}

template <class TYPE>
Matriz<TYPE> Matriz<TYPE>::operator*(const TYPE alfa){
    Matriz<TYPE> result(this->rows(), this->cols());
    for(int i = 0; i < this->rows(); i++)
        for(int j = 0; j < this->cols(); j++)
            result.set_value(i, j, this->get_value(i, j) * alfa);
    return result;
}

template <class TYPE>
Matriz<TYPE> Matriz<TYPE>::operator/(const TYPE alfa){
    Matriz<TYPE> result(this->rows(), this->cols());
    for(int i = 0; i < this->rows(); i++)
        for(int j = 0; j < this->cols(); j++)
            result.set_value(i, j, this->get_value(i, j)/alfa);
    return result;
}

template <class TYPE>
Matriz<TYPE> Matriz<TYPE>::operator*(const Matriz<TYPE>& m){
    Matriz<TYPE> result(this->rows(), m.cols());
    if(this->verify_row_col(m)) result.set_null();
    for(int i = 0; i < result.rows(); i++){
        for(int j = 0; j < result.cols(); j++){
            result.set_value(i, j, this->get_row(i) * m.get_col(j));
        }
    }
    return result;
}

template <class TYPE>
Vetor<TYPE> Matriz<TYPE>::operator*(const Vetor<TYPE>& v){
    Vetor<TYPE> result(this->rows());
    if(this->verify_row_ele(v)) result.set_null();
    for(int i = 0; i < result.length(); i++){
        result.set_value(i, this->get_row(i) * v);
    }
    return result;
}

template <class TYPE>
void Matriz<TYPE>::operator+=(const Matriz<TYPE>& m){
    if(this->verify_dim(m)) return;
    for(int i = 0; i < this->rows(); i++)
        for(int j = 0; j < this->cols(); j++)
            this->set_value(i, j, m.get_value(i, j) + this->get_value(i, j));
}

template <class TYPE>
void Matriz<TYPE>::operator-=(const Matriz<TYPE>& m){
    if(this->verify_dim(m)) return;
    for(int i = 0; i < this->rows(); i++)
        for(int j = 0; j < this->cols(); j++)
            this->set_value(i, j, this->get_value(i, j) - m.get_value(i, j));
}

template <class TYPE>
void Matriz<TYPE>::operator*=(const TYPE alfa){
    for(int i = 0; i < this->rows(); i++)
        for(int j = 0; j < this->cols(); j++)
            this->set_value(i, j, this->get_value(i, j) * alfa);
}

template <class TYPE>
void Matriz<TYPE>::operator/=(const TYPE alfa){
    for(int i = 0; i < this->rows(); i++)
        for(int j = 0; j < this->cols(); j++)
            this->set_value(i, j, this->get_value(i, j)/alfa);
}

#endif