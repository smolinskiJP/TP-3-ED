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

    void QuicksortR(int l, int r);
    void Partition(int l, int r, int* i, int* j);
    void Swap(T* a, T* b);
    int Median(int a, int b, int c);
public:
    DynamicArray();
    ~DynamicArray();

    void Push(T value);

    int GetSize();
    
    T& operator[](int index);
    void Print();
    void Sort();
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

template <typename T>
void DynamicArray<T>::Sort(){
    if(this->_size > 1) this->QuicksortR(0, this->_size - 1);
}

template <typename T>
void DynamicArray<T>::QuicksortR(int l, int r){
    if(l >= r) return;
    int i, j;

    this->Partition(l, r, &i, &j);

    this->QuicksortR(l, j);
    this->QuicksortR(i, r);
}

template <typename T>
void DynamicArray<T>::Partition(int l, int r, int* i, int* j){
    (*i) = l;
    (*j) = r;

    int pivot = this->Median(l, r, (l + r)/2);

    do{
        while(this->_data[pivot] > this->_data[*i]) (*i)++;
        while(this->_data[pivot] < this->_data[*j]) (*j)--;

        if((*i) <= (*j)){
            this->Swap(&(this->_data[*i]), &(this->_data[*j]));
            (*i)++;
            (*j)--;
        }
    }while(*i <= *j);
}

template <typename T>
void DynamicArray<T>::Swap(T* a, T* b){
    T temp = *a;
    *a = *b;
    *b = temp;
}

template <typename T>
int DynamicArray<T>::Median(int a, int b, int c){
    if(this->_data[b] < this->_data[a]){ // _ b _ a _
        if(this->_data[c] < this->_data[b]) return b; // c b a
        if(this->_data[c] < this->_data[a]) return c; // b c a
        return a; // b a c
    } // _ a _ b _
    if(this->_data[c] < this->_data[a]) return a; // c a b
    if(this->_data[c] < this->_data[b]) return c; // a c b
    return b; // a b c
}

#endif