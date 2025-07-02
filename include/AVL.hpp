#ifndef AVL_HPP
#define AVL_HPP

#include <iostream>
#include "Node.hpp"

template <typename K, typename V>
class AVL{
    private:
        Node<K, V>* _root;

        Node<K, V>* RotateRight(Node<K, V>* node);
        Node<K, V>* RotateLeft(Node<K, V>* node);
        
        Node<K, V>* InsertR(Node<K, V>* node, K key, V value);
        Node<K, V>* FindR(Node<K, V>* node, K key);
        void DeleteR(Node<K, V>* node);

    public:
        AVL();
        ~AVL();

        void Insert(K key, V value);
        V Find(K key);
};

template <typename K, typename V>
Node<K, V>* AVL<K, V>::RotateRight(Node<K, V>* node){
    Node<K, V>* new_parent = node->GetLeft();
    Node<K, V>* new_left_child = new_parent->GetRight();

    new_parent->SetRight(node);
    node->SetLeft(new_left_child);

    node->UpdateHeight();
    new_parent->UpdateHeight();

    return new_parent;
}

template <typename K, typename V>
Node<K, V>* AVL<K, V>::RotateLeft(Node<K, V>* node){
    Node<K, V>* new_parent = node->GetRight();
    Node<K, V>* new_right_child = new_parent->GetLeft();

    new_parent->SetLeft(node);
    node->SetRight(new_right_child);

    node->UpdateHeight();
    new_parent->UpdateHeight();

    return new_parent;
}

template <typename K, typename V>
Node<K, V>* AVL<K, V>::InsertR(Node<K, V>* node, K key, V value){
    if(!node) return new Node<K, V>(key, value);

    if (key < node->GetKey()) node->SetLeft(InsertR(node->GetLeft(), key, value));
    else if (key > node->GetKey()) node->SetRight(InsertR(node->GetRight(), key, value));
    else{
        node->SetValue(value);
        return node;
    }

    node->UpdateHeight();
    int balance = node->GetBalance();

    // Caso Esquerda-Esquerda
    if (balance > 1 && key < node->GetLeft()->GetKey()) 
        return this->RotateRight(node);
    
    // Caso Direita-Direita
    if (balance < -1 && key > node->GetRight()->GetKey()) 
        return this->RotateLeft(node);

    // Caso Esquerda-Direita
    if (balance > 1 && key > node->GetLeft()->GetKey()) {
        node->SetLeft(this->RotateLeft(node->GetLeft()));
        return this->RotateRight(node);
    }
    
    // Caso Direita-Esquerda
    if (balance < -1 && key < node->GetRight()->GetKey()){
        node->SetRight(this->RotateRight(node->GetRight()));
        return this->RotateLeft(node);
    }

    return node;
}

template <typename K, typename V>
Node<K, V>* AVL<K, V>::FindR(Node<K, V>* node, K key){
    if(!node) return nullptr;

    if(key < node->GetKey()) return FindR(node->GetLeft(), key);
    if(key > node->GetKey()) return FindR(node->GetRight(), key);
    return node;
}

template <typename K, typename V>
void AVL<K, V>::DeleteR(Node<K, V>* node){
    if(node){
        DeleteR(node->GetLeft());
        DeleteR(node->GetRight());
        delete node->GetValue();
        delete node;
    }
}

template <typename K, typename V>
AVL<K, V>::AVL() : _root(nullptr){}

template <typename K, typename V>
AVL<K, V>::~AVL(){
    this->DeleteR(this->_root);
}

template <typename K, typename V>
void AVL<K, V>::Insert(K key, V value){
    this->_root = this->InsertR(this->_root, key, value);
}

template <typename K, typename V>
V AVL<K, V>::Find(K key){
    Node<K, V>* result = this->FindR(this->_root, key);
    if(result) return result->GetValue();
    throw std::logic_error("Value not found in AVL");
}

#endif