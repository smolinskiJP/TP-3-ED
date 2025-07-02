#ifndef AVL_HPP
#define AVL_HPP

#include <iostream>
#include "Node.hpp"

template <typename T>
class AVL{
    private:
        Node<T>* _root;

        Node<T>* RotateRight(Node<T>* node);
        Node<T>* RotateLeft(Node<T>* node);
        
        Node<T>* InsertR(Node<T>* node, T data);
        Node<T>* FindR(Node<T>* node, T data);
        void DeleteR(Node<T>* node);

    public:
        AVL();
        ~AVL();

        void Insert(T data);
        T* Find(T data);
};

template <typename T>
Node<T>* AVL<T>::RotateRight(Node<T>* node){
    Node<T>* new_parent = node->GetLeft();
    Node<T>* new_left_child = new_parent->GetRight();

    new_parent->SetRight(node);
    node->SetLeft(new_left_child);

    node->UpdateHeight();
    new_parent->UpdateHeight();
}

template <typename T>
Node<T>* AVL<T>::RotateLeft(Node<T>* node){
    Node<T>* new_parent = node->GetRight();
    Node<T>* new_right_child = new_parent->GetLeft();

    new_parent->SetLeft(node);
    node->SetRight(new_right_child);

    node->UpdateHeight();
    new_parent->UpdateHeight();
}

template <typename T>
Node<T>* AVL<T>::InsertR(Node<T>* node, T data){
    if(!node) return new Node<T>(data);

    if (data < node->GetData()) node->SetLeft(InsertR(node->GetLeft(), data));
    else if (data > node->GetData()) node->SetRight(InsertR(node->GetRight(), data));
    else return node;

    node->UpdateHeight();
    int balance = node->GetBalance();

    if(balance < 1 && balance > -1) return node;
    if (balance > 1 && data < node->GetLeft()->GetData()) return this->RotateRight(node);
    if (balance > 1 && data > node->GetLeft()->GetData()) {
        node->SetLeft(this->RotateLeft(node->GetLeft()));
        return this->RotateRight(node);
    }
    if (balance < -1 && data > node->GetRight()->GetData()) return this->RotateLeft(node);
    if (balance < -1 && data < node->GetRight()->GetData()) {
        node->SetRight(this->RotateRight(node->GetRight()));
        return this->RotateLeft(node);
    }
}

template <typename T>
Node<T>* AVL<T>::FindR(Node<T>* node, T data){
    if(!node) return nullptr;

    if(data < node->GetData()) return FindR(node->GetLeft(), data);
    if(data > node->GetData()) return FindR(node->GetRight(), data);
    return node;
}

template <typename T>
void AVL<T>::DeleteR(Node<T>* node){
    if(node){
        DeleteR(node->GetLeft());
        DeleteR(node->GetRight());
        delete node;
    }
}

template <typename T>
AVL<T>::AVL() : _root(nullptr){}

template <typename T>
AVL<T>::~AVL(){
    this->DeleteR(this->_root);
}

template <typename T>
void AVL<T>::Insert(T data){
    this->_root = this->InsertR(this->_root, data);
}

template <typename T>
T* AVL<T>::Find(T data){
    Node<T>* result = this->FindR(this->_root, data);
    return (result) ? &(result->GetData()) : nullptr;
}

#endif