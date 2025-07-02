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

//Rotaciona um node para a direita, realocando seus nodes "filhos"
template <typename K, typename V>
Node<K, V>* AVL<K, V>::RotateRight(Node<K, V>* node){
    //O novo node pai sera o filho a esquerda do centro de rotacao
    Node<K, V>* new_parent = node->GetLeft();
    //O novo filho a esquerda do centro de rotacao vai ser o filho da direita do antigo filho a esquerda
    Node<K, V>* new_left_child = new_parent->GetRight();

    //Adiciona o centro da rotacao como novo filho a direita do novo pai
    new_parent->SetRight(node);
    //Atualiza o filho a esquerda do centro de rotacao
    node->SetLeft(new_left_child);

    //Atualiza a altura do node centro e novo pai
    node->UpdateHeight();
    new_parent->UpdateHeight();

    //Retorna o novo pai para que a subarvore tenha ele como raiz
    return new_parent;
}

//Rotaciona um node para a esquerda, realocando seus nodes "filhos"
template <typename K, typename V>
Node<K, V>* AVL<K, V>::RotateLeft(Node<K, V>* node){
    //O novo node pai sera o filho a direita do centro de rotacao
    Node<K, V>* new_parent = node->GetRight();
    //O novo filho a direita do centro de rotacao vai ser o filho da esquerda do antigo filho a esquerda
    Node<K, V>* new_right_child = new_parent->GetLeft();

    //Adiciona o centro da rotacao como novo filho a esquerda do novo pai
    new_parent->SetLeft(node);
    //Atualiza o filho a direita do centro de rotacao
    node->SetRight(new_right_child);

    //Atualiza a altura do node centro e novo pai
    node->UpdateHeight();
    new_parent->UpdateHeight();

    //Retorna o novo pai para que a subarvore tenha ele como raiz
    return new_parent;
}

//Insercao recursiva em um node
template <typename K, typename V>
Node<K, V>* AVL<K, V>::InsertR(Node<K, V>* node, K key, V value){
    //Caso chegue em uma folha, cria novo node
    if(!node) return new Node<K, V>(key, value);

    //Verifica onde deve adicionar o novo valor
    //Se a chave for menor que o node atual, deve seguir a esquerda
    if (key < node->GetKey()) node->SetLeft(InsertR(node->GetLeft(), key, value));
    //Se a chave for maior que o node atual, deve seguir a direita
    else if (key > node->GetKey()) node->SetRight(InsertR(node->GetRight(), key, value));
    //Se a chave for igual, atualiza o valor
    else{
        node->SetValue(value);
        return node;
    }

    //Atualiza o valor do node atual
    node->UpdateHeight();
    //Pega o balanceamento do node atual
    int balance = node->GetBalance();

    //Node desbalanceado (|Balance| > 1)
    /*Caso Esquerda-Esquerda
      o
     o
    o
    */
    if (balance > 1 && key < node->GetLeft()->GetKey()){
        //Uma rotacao para a direita sera o suficiente para concertar
        return this->RotateRight(node);
    }
    /*Caso Direita-Direita
    o
     o
      o
    */
    if (balance < -1 && key > node->GetRight()->GetKey()){
        //Uma rotacao para a esquerda sera o suficiente para concertar
        return this->RotateLeft(node);
    }
    /*Caso Esquerda-Direita
     o
    o
     o
    */
    if (balance > 1 && key > node->GetLeft()->GetKey()) {
        //Primeiro rotaciona o filho a esquerda para a esquerda
        node->SetLeft(this->RotateLeft(node->GetLeft()));
        //Entao rotaciona o atual para a direita
        return this->RotateRight(node);
    }
    /*Caso Direita-Esquerda
    o
     o
    o
    */
    if (balance < -1 && key < node->GetRight()->GetKey()){
        //Primeiro rotaciona o filho a direita para a direita
        node->SetRight(this->RotateRight(node->GetRight()));
        //Entao rotaciona o atual para a esquerda
        return this->RotateLeft(node);
    }

    //Retorna o node
    return node;
}

//Busca recursiva em um node
template <typename K, typename V>
Node<K, V>* AVL<K, V>::FindR(Node<K, V>* node, K key){
    //Retorna nulo caso nao exista (chave nao encontrada)
    if(!node) return nullptr;

    //Verifica por onde continuar as buscar
    //Se a chave for menor que a atual, siga a esquerda
    if(key < node->GetKey()) return FindR(node->GetLeft(), key);
    //Se a chave for maior que a atual, siga a direita
    if(key > node->GetKey()) return FindR(node->GetRight(), key);
    //Se for igual, retore
    return node;
}

//Delecao recursiva de um node
template <typename K, typename V>
void AVL<K, V>::DeleteR(Node<K, V>* node){
    if(node){
        //Caso o node exista, deleta ambos seus filhos, seu conteudo e por fim a si mesmo
        DeleteR(node->GetLeft());
        DeleteR(node->GetRight());
        delete node->GetValue();
        delete node;
    }
}

//Construtor padrao, inicia a raiz como nula
template <typename K, typename V>
AVL<K, V>::AVL() : _root(nullptr){}

//Destrutor padrao, chama a destruicao recursiva a partir da raiz
template <typename K, typename V>
AVL<K, V>::~AVL(){
    this->DeleteR(this->_root);
}

//Insere um valor associado a uma chave na AVL
template <typename K, typename V>
void AVL<K, V>::Insert(K key, V value){
    //Chama a insercao recursiva a partir da raiz
    this->_root = this->InsertR(this->_root, key, value);
}

//Procura o valor de uma chave na AVK
template <typename K, typename V>
V AVL<K, V>::Find(K key){
    //Pega o node de resultado chamando a busca recursiva a partir da raiz
    Node<K, V>* result = this->FindR(this->_root, key);
    //Caso exista retorna, caso nao exista lanca excecao
    if(result) return result->GetValue();
    throw std::logic_error("Value not found in AVL");
}

#endif