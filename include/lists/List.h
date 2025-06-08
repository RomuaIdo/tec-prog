#ifndef LIST_H
#define LIST_H

#include "Element.h"
#include "Iterator.h"
#include <cstddef> // size_t

template <typename T>
class List {
public:
    typedef ListIterator<T> iterator;
    //typedef ConstListIterator<T> const_iterator;
    
    List() : head(0), tail(0), size_(0) {}
    ~List() { clear(); }
    
    List(const List& other) : head(0), tail(0), size_(0) {
        for (const Node<T>* n = other.head; n; n = n->next) {
            push_back(n->data);
        }
    }
    
    List& operator=(const List& other) {
        if (this != &other) {
            clear();
            for (const Node<T>* n = other.head; n; n = n->next) {
                push_back(n->data);
            }
        }
        return *this;
    }
    
    void push_back(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        if (!tail) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        ++size_;
    }
    
    void push_front(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        if (!head) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        ++size_;
    }
    
    iterator erase(iterator pos) {
        Node<T>* n = pos.ptr;
        if (!n) return end();
        
        iterator next(n->next);
        
        if (n->prev) n->prev->next = n->next;
        else head = n->next;
        
        if (n->next) n->next->prev = n->prev;
        else tail = n->prev;
        
        delete n;
        --size_;
        return next;
    }
    
    void clear() {
        Node<T>* n = head;
        while (n) {
            Node<T>* next = n->next;
            delete n;
            n = next;
        }
        head = tail = 0;
        size_ = 0;
    }
    
    bool empty() const { return size_ == 0; }
    size_t size() const { return size_; }
    
    iterator begin() { return iterator(head); }
    iterator end() { return iterator(0); }
    
    //const_iterator begin() const { return const_iterator(head); }
    //const_iterator end() const { return const_iterator(0); }

private:
    Node<T>* head;
    Node<T>* tail;
    size_t size_;
};

#endif
