#ifndef NODE_HPP
#define NODE_HPP

template <typename K, typename V>
class Node{
    private:
        K _key;
        V _value;
        Node<K, V>* _right;
        Node<K, V>* _left;  
        int _height;
    public:
        Node(K key, V value);
        ~Node();

        int GetHeight();
        void UpdateHeight();
        int GetBalance();
        int Max(int a, int b);
        
        Node<K, V>* GetRight();
        void SetRight(Node<K, V>* value);
        Node<K, V>* GetLeft();
        void SetLeft(Node<K, V>* value);

        V GetValue();
        void SetValue(V value);
        K GetKey();
};

//Construtor padrao de node, recebe chave e valor
template <typename K, typename V>
Node<K, V>::Node(K key, V value) : _key(key), _value(value), _right(nullptr), _left(nullptr), _height(0){}

//Destrutor padrao
template <typename K, typename V>
Node<K, V>::~Node(){}

//Retorna a altura relativa a um node
template <typename K, typename V>
int Node<K, V>::GetHeight(){
    return this->_height;
}

//Atualiza a altura de um node
template <typename K, typename V>
void Node<K, V>::UpdateHeight(){
    //Iniciando as alturas laterais em -1 os nodes folha ficam com altura relativa 0.
    int left_h = -1, right_h = -1;
    if(this->_left) left_h = this->_left->GetHeight();
    if(this->_right) right_h = this->_right->GetHeight();
    //A altura sera o maximo de suas alturas laterais +1
    this->_height = 1 + Max(left_h, right_h);
}

//Retorna o balanceamento de um no
template <typename K, typename V>
int Node<K, V>::GetBalance(){
    int left_h = -1, right_h = -1;
    if(this->_left) left_h = this->_left->GetHeight();
    if(this->_right) right_h = this->_right->GetHeight();
    //O balanceamento sera a diferenca entre as alturas laterais
    return left_h - right_h;
}

//Retorna o maximo entre dois inteiros
template <typename K, typename V>
int Node<K, V>::Max(int a, int b){
    return (a > b) ? a : b;
}

//Retorna o valor a direita de um node
template <typename K, typename V>
Node<K, V>* Node<K, V>::GetRight(){
    return this->_right;
}

//Define o valor a direita de um node na
template <typename K, typename V>
void Node<K, V>::SetRight(Node<K, V>* value){
    this->_right = value;
}

//Retorna o valor a esquerda de um node na
template <typename K, typename V>
Node<K, V>* Node<K, V>::GetLeft(){
    return this->_left;
}

//Define o valor a esquerda de um node na
template <typename K, typename V>
void Node<K, V>::SetLeft(Node<K, V>* value){
    this->_left = value;
}

//Retorna o valor de um node
template <typename K, typename V>
V Node<K, V>::GetValue(){
    return this->_value;
}

//Define o valor de um node
template <typename K, typename V>
void Node<K, V>::SetValue(V value){
    this->_value = value;
}

//Retorna a chave de um node
template <typename K, typename V>
K Node<K, V>::GetKey(){
    return this->_key;
}

#endif