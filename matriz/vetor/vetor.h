#ifndef VETOR
#define VETOR
#include <string>
#include <cmath>
#include <iostream>

using namespace std;

// Alison de Oliveira Tristao
// github.com/AlisonTristao

// ********************************
// *       Class of Vectors       *
// ********************************

/*
    CUIDADO NA INTERAÇÂO DE VETORES DE TAMANHOS DIFERENTES
    ao acessar itens fora do tamanho do vetor, as funções retornam zero

    ex multiplicação linha x coluna:
    (ele vai completar o dado que falta com zeros)

    [1, 2, 4] * [1]
                [2]
                [0] <-
*/

template <class TYPE>
class vetor {
    private:
        int arr_size;
        TYPE* arr_data;
    public:
        vetor(){}; // default constructor
        vetor(int size){
            set_size(size);
        };
        void set_size(int size){
            arr_size = size;
            arr_data = new TYPE[size];
            static TYPE default_value;
            for(int i = 0; i < size; i++) // preenche com zeros
                arr_data[i] = default_value;
        };
        virtual ~vetor(){
            delete[] arr_data;
        };

        // manipulação dos dados
        void set_value(int index, TYPE value);
        const TYPE get_value(int index) const;
        vetor<double> get_unit_vector();
        double get_module();
        const int length() const;
        string text();

        // alltera os operadores
        const TYPE operator[](int index) const;
        vetor<TYPE> operator+(const vetor<TYPE>& v);
        vetor<TYPE> operator-(const vetor<TYPE>& v);
        vetor<TYPE> operator*(const TYPE alfa) const;
        vetor<TYPE> operator/(const TYPE alfa) const; // cuidado com vetores int
        // vetor linha * vetor coluna
        TYPE operator*(const vetor<TYPE>& v);

        // opradores que nao retornam nada
        void operator=(const vetor<TYPE> v);
        void operator+=(const vetor<TYPE>& v);
        void operator-=(const vetor<TYPE>& v);
        void operator*=(const TYPE alfa);
        void operator/=(const TYPE alfa); // cuidado com vetores int
};

template <class TYPE>
string vetor<TYPE>::text(){
    // ex: [1, 2, 3]
    string text = "[";
    for(int i = 0; i < arr_size; i++){
        text += to_string(arr_data[i]);
        if(i < arr_size - 1) text += ", ";
    }
    text += "]";
    return text; 
}

template <class TYPE>
void vetor<TYPE>::set_value(int index, TYPE value){
    if(index < 0 || index >= arr_size) return;
    arr_data[index] = value;
}

template <class TYPE>
const TYPE vetor<TYPE>::get_value(int index) const{
    if(index < 0 || index >= arr_size){
        static TYPE default_value;
        return default_value;
    }
    return arr_data[index]; 
}

template <class TYPE>
const int vetor<TYPE>::length() const{
    return arr_size; 
}

template <class TYPE>
const TYPE vetor<TYPE>::operator[](int index) const {
    if(index < 0 || index >= arr_size){
        static TYPE default_value;
        return default_value;
    }
    return arr_data[index]; 
}

template <class TYPE>
double vetor<TYPE>::get_module(){
    // soma os elemtnos ao quadrado
    TYPE sum_quadratic_elemts = 0;    
    for(int i = 0; i < arr_size; i++)
        sum_quadratic_elemts += arr_data[i]*arr_data[i];
    // retorna a raiz da soma
    return sqrt(sum_quadratic_elemts);
}

template <class TYPE>
vetor<double> vetor<TYPE>::get_unit_vector(){
    vetor<double> unit_vector(arr_size); // vetor unitario
    // calcula o modulo do vetor atual
    double module = this->get_module();
    // define a dimensao de cada elemento
    for(int i = 0; i < arr_size; i++)
        unit_vector.set_value(i, arr_data[i]/module);
    return unit_vector; 
}

// cuidado com arryas definidos com tamanho diferentes
template <class TYPE>
void vetor<TYPE>::operator=(const vetor<TYPE> v){
    for(int i = 0; i < arr_size; i++)
        arr_data[i] = v[i];
}

template <class TYPE>
vetor<TYPE> vetor<TYPE>::operator+(const vetor<TYPE>& v){
    // maior comprimento de cada
    int max_length = (v.length() > this->length()) ? v.length() : this->length();
    // completa os numeros vazios com 0
    vetor<TYPE> result(max_length);
    for(int i = 0; i < max_length; i++)
        result.set_value(i, v[i] + arr_data[i]);
    return result;
}

template <class TYPE>
vetor<TYPE> vetor<TYPE>::operator-(const vetor<TYPE>& v){
    // maior comprimento de cada
    int max_length = (v.length() > this->length()) ? v.length() : this->length();
    // completa os numeros vazios com 0
    vetor<TYPE> result(max_length);
    for(int i = 0; i < arr_size; i++)
        result.set_value(i, arr_data[i] - v[i]);
    return result;
}

// cuidado divisao por inteiros
template <class TYPE>
vetor<TYPE> vetor<TYPE>::operator/(const TYPE alfa) const{
    vetor<TYPE> result(arr_size); 
    for(int i = 0; i < arr_size; i++)
        result.set_value(i, arr_data[i]/alfa);
    return result; 
}

template <class TYPE>
vetor<TYPE> vetor<TYPE>::operator*(const TYPE alfa) const{
    vetor<TYPE> result(arr_size); 
    for(int i = 0; i < arr_size; i++)
        result.set_value(i, arr_data[i]*alfa);
    return result; 
}

template <class TYPE>
TYPE vetor<TYPE>::operator*(const vetor<TYPE>& v){
    static TYPE result;
    // tconsidera que é zero se for tamanhos diferentes
    int max_length = (v.length() > this->length()) ? v.length() : this->length();
    for(int i = 0; i < max_length; i++)
        result += arr_data[i] * v[i];
    return result; 
}

template <class TYPE>
void vetor<TYPE>::operator+=(const vetor<TYPE>& v){
    int max_length = (v.length() > this->length()) ? v.length() : this->length();
    // completa os numeros vazios com 0
    for(int i = 0; i < max_length; i++)
        arr_data[i] = v[i] + arr_data[i];
}

template <class TYPE>
void vetor<TYPE>::operator-=(const vetor<TYPE>& v){
    int max_length = (v.length() > this->length()) ? v.length() : this->length();
    // completa os numeros vazios com 0
    for(int i = 0; i < max_length; i++)
        arr_data[i] = arr_data[i] - v[i];
}

template <class TYPE>
void vetor<TYPE>::operator*=(const TYPE alfa){
    for(int i = 0; i < arr_size; i++)
        arr_data[i] *= alfa;
}

template <class TYPE>
void vetor<TYPE>::operator/=(const TYPE alfa){
    for(int i = 0; i < arr_size; i++)
        arr_data[i] /= alfa;
}

#endif