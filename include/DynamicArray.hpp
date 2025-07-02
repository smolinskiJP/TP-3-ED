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
    void Sort();
};

//Funcao de Resize (Aumento de limite) do Array
template <typename T>
void DynamicArray<T>::Resize(){
    //Inicia com 1 se o tamanho for 0 ou dobra o tamanho atual
    this->_max_size = (this->_max_size == 0) ? 1 : this->_max_size * 2;

    //Aloca a memoria necessaria
    T* new_data = new T[this->_max_size];

    //Transfere os dados para o novo Array
    for(int i = 0; i < this->_size; i++){
        new_data[i] = this->_data[i];
    }

    //Deleta o Array antigo
    delete[] this->_data;
    this->_data = new_data;
}

//Construtor padrao do Array
template <typename T>
DynamicArray<T>::DynamicArray() : 
    _data(nullptr), _max_size(0), _size(0){
    //Inicia tamanhos com 0 mas chama o primeiro resize para criar um Array minimo (tamanho 1)
    this->Resize();
}

//Destrutor padrao do Array
template <typename T>
DynamicArray<T>::~DynamicArray(){
    delete[] this->_data;
}

//Adiciona valor ao fim do Array
template <typename T>
void DynamicArray<T>::Push(T value){
    if(this->_size == this->_max_size) this->Resize();
    this->_data[this->_size++] = value;
}

//Retorna o tamanho do Array
template <typename T>
int DynamicArray<T>::GetSize(){
    return this->_size;
}

//Sobrecarga do operador de acesso por index
template <typename T>
T& DynamicArray<T>::operator[](int index){
    //Retorna erro caso esteja fora dos limites
    if(index >= this->_size) throw std::out_of_range("Out of range");
    return this->_data[index];
}

//Ordena o Array
template <typename T>
void DynamicArray<T>::Sort(){
    if(this->_size > 1) this->QuicksortR(0, this->_size - 1);
}

//Ordenacao baseada no algoritmo de QuickSort com mediana de 3
template <typename T>
void DynamicArray<T>::QuicksortR(int l, int r){
    if(l >= r) return; //Caso base: Particao com menos de 2 elementos
    //Passo recursivo

    int i, j;

    //Particiona o vetor
    this->Partition(l, r, &i, &j);

    //Chama recursivamente para cada uma das particoes
    this->QuicksortR(l, j);
    this->QuicksortR(i, r);
}

//Particionamento de um vetor em dois menores e separados por um pivo
template <typename T>
void DynamicArray<T>::Partition(int l, int r, int* i, int* j){
    (*i) = l;
    (*j) = r;

    //Calcula o pivo como mediana do primeiro, ultimo e valor do meio para evitar o caso O(n^2)
    int pivot = this->Median(l, r, (l + r)/2);

    do{
        //Avanca o ponteiro da esqueda ate encontrar um elemento maior ou igual ao pivo
        while(this->_data[pivot] > this->_data[*i]) (*i)++;

        //Retrocede o ponteiro da direita ate encontrar um elemento menor ou igual ao pivo
        while(this->_data[pivot] < this->_data[*j]) (*j)--;

        if((*i) <= (*j)){ //Se o ponteiro da esquerda esta a esquerda do ponteiro da direita troca seus valores e incrementa cada um deles
            this->Swap(&(this->_data[*i]), &(this->_data[*j]));
            (*i)++;
            (*j)--;
        }
    //Executa enquanto o ponteiro da esquerda estiver a esquerda do ponteiro da direita
    }while(*i <= *j);
}

//Metodo de troca de valores
template <typename T>
void DynamicArray<T>::Swap(T* a, T* b){
    T temp = *a;
    *a = *b;
    *b = temp;
}

//Mediana de tres posicoes em um Array
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