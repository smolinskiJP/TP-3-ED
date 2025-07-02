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

template <typename K, typename V>
Node<K, V>::Node(K key, V value) : _key(key), _value(value), _right(nullptr), _left(nullptr), _height(0){}

template <typename K, typename V>
Node<K, V>::~Node(){}

template <typename K, typename V>
int Node<K, V>::GetHeight(){
    return this->_height;
}

template <typename K, typename V>
void Node<K, V>::UpdateHeight(){
    int left_h = -1, right_h = -1;
    if(this->_left) left_h = this->_left->GetHeight();
    if(this->_right) right_h = this->_right->GetHeight();
    this->_height = 1 + Max(left_h, right_h);
}

template <typename K, typename V>
int Node<K, V>::GetBalance(){
    int left_h = -1, right_h = -1;
    if(this->_left) left_h = this->_left->GetHeight();
    if(this->_right) right_h = this->_right->GetHeight();
    return left_h - right_h;
}

template <typename K, typename V>
int Node<K, V>::Max(int a, int b){
    return (a > b) ? a : b;
}

template <typename K, typename V>
Node<K, V>* Node<K, V>::GetRight(){
    return this->_right;
}

template <typename K, typename V>
void Node<K, V>::SetRight(Node<K, V>* value){
    this->_right = value;
}

template <typename K, typename V>
Node<K, V>* Node<K, V>::GetLeft(){
    return this->_left;
}

template <typename K, typename V>
void Node<K, V>::SetLeft(Node<K, V>* value){
    this->_left = value;
}

template <typename K, typename V>
V Node<K, V>::GetValue(){
    return this->_value;
}

template <typename K, typename V>
void Node<K, V>::SetValue(V value){
    this->_value = value;
}

template <typename K, typename V>
K Node<K, V>::GetKey(){
    return this->_key;
}

#endif