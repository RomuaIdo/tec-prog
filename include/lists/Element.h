#ifndef ELEMENT_H
#define ELEMENT_H

template <typename T>
class Node {
private:
    T data;
    Node<T>* next;
    Node<T>* prev;

    // Construtor privado
    Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}

    // Permite acesso direto apenas para List e iteradores
    template <typename U> friend class List;
    template <typename U> friend class ListIterator;
    template <typename U> friend class ConstListIterator;

public:
    Node() : data(T()), next(nullptr), prev(nullptr) {}
    ~Node() {}

    T& getData() { return data; }
    void setData(const T& value) { data = value; }
    Node<T>* getNext() { return next; }
    Node<T>* getPrev() { return prev; }

    void setNext(Node<T>* n) { next = n; }
    void setPrev(Node<T>* p) { prev = p; }
};

#endif
