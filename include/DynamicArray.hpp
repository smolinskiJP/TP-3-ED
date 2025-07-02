#ifndef DYNAMIC_ARRAY_HPP
#define DYNAMIC_ARRAY_HPP

#include <iostream>

template <typename T>
class DynamicArray {
private:
    T* _data;
    int _max_size;
    int _size;

    void Resize();
public:
    DynamicArray();
    ~DynamicArray();

    void Push(T value);

    int GetSize();
    
    T& operator[](int index);
    void Print();
};

template <typename T>
void DynamicArray<T>::Resize(){
    this->_max_size = (this->_max_size == 0) ? 1 : this->_max_size * 2;
    T* new_data = new T[this->_max_size];
    for(int i = 0; i < this->_size; i++){
        new_data[i] = this->_data[i];
    }
    delete[] this->_data;
    this->_data = new_data;
}

template <typename T>
DynamicArray<T>::DynamicArray() : 
    _data(nullptr), _max_size(0), _size(0){
    this->Resize();
}

template <typename T>
DynamicArray<T>::~DynamicArray(){
    delete[] this->_data;
}

template <typename T>
void DynamicArray<T>::Push(T value){
    if(this->_size == this->_max_size) this->Resize();
    this->_data[this->_size++] = value;
}

template <typename T>
int DynamicArray<T>::GetSize(){
    return this->_size;
}

template <typename T>
T& DynamicArray<T>::operator[](int index){
    if(index >= this->_size) throw std::out_of_range("Out of range");
    return this->_data[index];
}

template <typename T>
void DynamicArray<T>::Print(){
    for(int i = 0; i < this->_size; i++){
        std::cout << this->_data[i] << " ";
    }
    std::cout << std::endl;
}

#endif