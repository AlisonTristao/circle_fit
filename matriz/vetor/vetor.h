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
        virtual ~vetor(){
            delete[] arr_data;
        };
        void set_null(){
            arr_data = nullptr;
            arr_size = 0;
        };
        void set_size(int size){
            arr_size = size;
            arr_data = new TYPE[size];
            TYPE default_value = 0;
            for(int i = 0; i < size; i++) // preenche com zeros
                arr_data[i] = default_value;
        };

        // manipulação dos dados
        bool verify_dim(const vetor<TYPE>& v);
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
        vetor<TYPE> operator*(const TYPE alfa);
        vetor<TYPE> operator/(const TYPE alfa); // cuidado com vetores int
        // vetor linha * vetor coluna
        TYPE operator*(const vetor<TYPE>& v);

        // opradores que nao retornam nada
        void operator=(const vetor<TYPE> v);
        void operator+=(const vetor<TYPE>& v);
        void operator-=(const vetor<TYPE>& v);
        void operator*=(const TYPE alfa);
        void operator/=(const TYPE alfa); // cuidado com vetores int
};

// mude acao de erro nessas 3 funcoes seguintes
template <class TYPE>
bool vetor<TYPE>::verify_dim(const vetor<TYPE>& v){
    if(this->length() != v.length()){
        cout << "Vetores com dimensoes diferentes" << endl;
        return true;
    }
    return false;
}

template <class TYPE>
void vetor<TYPE>::set_value(int index, TYPE value){
    if(index < 0 || index >= arr_size){
        cout << "Index inexistente (matriz.set_value)" << endl;
        return;
    }
    arr_data[index] = value;
}

template <class TYPE>
const TYPE vetor<TYPE>::get_value(int index) const{
    if(index < 0 || index >= arr_size){
        cout << "Index inexistente (vetor.get_value)" << endl;
        TYPE default_value = 0;
        return default_value;
    }
    return arr_data[index]; 
}

template <class TYPE>
string vetor<TYPE>::text(){
    // ex: [1, 2, 3]
    string text = "[";
    for(int i = 0; i < arr_size; i++){
        text += to_string(this->get_value(i));
        if(i < arr_size - 1) text += ", ";
    }
    if(!arr_size) text += "NULL"; // obj null
    text += "]";
    return text; 
}

template <class TYPE>
const int vetor<TYPE>::length() const{
    return arr_size; 
}

template <class TYPE>
const TYPE vetor<TYPE>::operator[](int index) const {
    return this->get_value(index); 
}

template <class TYPE>
double vetor<TYPE>::get_module(){
    // soma os elemtnos ao quadrado
    TYPE sum_quadratic_elemts = 0;    
    for(int i = 0; i < arr_size; i++)
        sum_quadratic_elemts += this->get_value(i)*this->get_value(i);
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
        unit_vector.set_value(i, this->get_value(i)/module);
    return unit_vector; 
}

template <class TYPE>
void vetor<TYPE>::operator=(const vetor<TYPE> v){
    for(int i = 0; i < arr_size; i++)
        this->set_value(i, v[i]);
}

template <class TYPE>
vetor<TYPE> vetor<TYPE>::operator+(const vetor<TYPE>& v){
    vetor<TYPE> result(this->length());
    if(this->verify_dim(v)) result.set_null(); // obj null
    for(int i = 0; i < result.length(); i++)
        result.set_value(i, v[i] + this->get_value(i));
    return result;
}

template <class TYPE>
vetor<TYPE> vetor<TYPE>::operator-(const vetor<TYPE>& v){
    vetor<TYPE> result(this->length());
    if(this->verify_dim(v)) result.set_null(); // obj null
    for(int i = 0; i < arr_size; i++)
        result.set_value(i, this->get_value(i) - v[i]);
    return result;
}

// cuidado divisao por inteiros
template <class TYPE>
vetor<TYPE> vetor<TYPE>::operator/(const TYPE alfa){
    vetor<TYPE> result(arr_size); 
    for(int i = 0; i < arr_size; i++)
        result.set_value(i, this->get_value(i)/alfa);
    return result; 
}

template <class TYPE>
vetor<TYPE> vetor<TYPE>::operator*(const TYPE alfa){
    vetor<TYPE> result(arr_size); 
    for(int i = 0; i < arr_size; i++)
        result.set_value(i, this->get_value(i)*alfa);
    return result; 
}

template <class TYPE>
TYPE vetor<TYPE>::operator*(const vetor<TYPE>& v){
    TYPE result = 0;
    if(this->verify_dim(v)) return result; // obj null
    for(int i = 0; i < arr_size; i++)
        result += this->get_value(i) * v[i];
    return result; 
}

template <class TYPE>
void vetor<TYPE>::operator+=(const vetor<TYPE>& v){
    if(this->verify_dim(v)) this->set_null();
    for(int i = 0; i < arr_size; i++)
        this->set_value(i, v[i] + this->get_value(i));
}

template <class TYPE>
void vetor<TYPE>::operator-=(const vetor<TYPE>& v){
    if(this->verify_dim(v)) this->set_null();
    for(int i = 0; i < arr_size; i++)
        this->set_value(i, this->get_value(i) - v[i]);
}

template <class TYPE>
void vetor<TYPE>::operator*=(const TYPE alfa){
    for(int i = 0; i < arr_size; i++)
        this->set_value(i, this->get_value(i) * alfa);
}

template <class TYPE>
void vetor<TYPE>::operator/=(const TYPE alfa){
    for(int i = 0; i < arr_size; i++)
        this->set_value(i, this->get_value(i)/alfa);
}

#endif