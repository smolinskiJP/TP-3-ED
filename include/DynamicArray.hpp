#ifndef DYNAMIC_ARRAY_HPP
#define DYNAMIC_ARRAY_HPP

#include <iostream>

template <typename T>
class DynamicArray {
private:
public:
    void Push(T data);
    int GetSize();
    T& operator[](int indice);
    const T& operator[](int indice) const;
};

#endif