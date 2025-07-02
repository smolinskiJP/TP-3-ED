#ifndef NODE_HPP
#define NODE_HPP

template <typename T>
class Node{
    private:
        T _data;
        Node* _right;
        Node* _left;
        int _height;
    public:
        Node(T data);
        ~Node();

        int GetHeight();
        void UpdateHeight();
        int GetBalance();
        int Max(int a, int b);
        
        Node<T>* GetRight();
        void SetRight(Node<T>* value);
        Node<T>* GetLeft();
        void SetLeft(Node<T>* value);

        T GetData();
};

template <typename T>
Node<T>::Node(T data) : _data(data), _left(nullptr), _right(nullptr), _height(1){}

template <typename T>
Node<T>::~Node(){}

template <typename T>
int Node<T>::GetHeight(){
    return (!this) ? 0 : this->_height;
}

template <typename T>
void Node<T>::UpdateHeight(){
    if(!this) return;
    this->_height = 1 + Max(this->_left->GetHeight() - this->_right->GetHeight());
}

template <typename T>
int Node<T>::GetBalance(){
    if(!this) return 0;
    return this->_left->GetHeight() - this->_right->GetHeight();
}

template <typename T>
int Node<T>::Max(int a, int b){
    return (a > b) a : b;
}

template <typename T>
Node<T>* Node<T>::GetRight(){
    return this->_right;
}

template <typename T>
void Node<T>::SetRight(Node<T>* value){
    this->_right = value;
}

template <typename T>
Node<T>* Node<T>::GetLeft(){
    return this->_left;
}

template <typename T>
void Node<T>::SetLeft(Node<T>* value){
    this->_left = value;
}

template <typename T>
T Node<T>::GetData(){
    return this->_data;
}

#endif