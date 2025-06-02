#pragma once
#include <cstddef> // for size_t
#include <iterator>

template<typename T>
class List {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;
        Node(const T& d) : data(d), next(nullptr), prev(nullptr) {}
    };
    Node* head;
    Node* tail;
    size_t size_;

public:
    class iterator {
        friend class List;
    private:
        Node* ptr;
        explicit iterator(Node* n) : ptr(n) {}
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        iterator() : ptr(nullptr) {}
        iterator(const iterator& other) : ptr(other.ptr) {}

        iterator& operator=(const iterator& other) {
            if (this != &other) {
                ptr = other.ptr;
            }
            return *this;
        }

        reference operator*() const { return ptr->data; }
        pointer operator->() const { return &(ptr->data); }

        iterator& operator++() { 
            if (ptr) ptr = ptr->next;
            return *this;
        }
        iterator operator++(int) { 
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }
        iterator& operator--() { 
            if (ptr) ptr = ptr->prev;
            return *this;
        }
        iterator operator--(int) { 
            iterator tmp = *this;
            --(*this);
            return tmp;
        }
        bool operator==(const iterator& other) const { return ptr == other.ptr; }
        bool operator!=(const iterator& other) const { return ptr != other.ptr; }
    };

    List() : head(nullptr), tail(nullptr), size_(0) {}
    ~List() { clear(); }

    List(const List& other) : head(nullptr), tail(nullptr), size_(0) {
        for (Node* n = other.head; n; n = n->next)
            push_back(n->data);
    }

    List& operator=(const List& other) {
        if (this != &other) {
            clear();
            for (Node* n = other.head; n; n = n->next)
                push_back(n->data);
        }
        return *this;
    }

    void push_back(const T& value) {
        Node* newNode = new Node(value);
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
        Node* newNode = new Node(value);
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
        Node* n = pos.ptr;
        if (!n) return end();
        iterator ret = iterator(n->next);
        if (n->prev) n->prev->next = n->next;
        else head = n->next;
        if (n->next) n->next->prev = n->prev;
        else tail = n->prev;
        delete n;
        --size_;
        return ret;
    }

    void clear() {
        Node* n = head;
        while (n) {
            Node* next = n->next;
            delete n;
            n = next;
        }
        head = tail = nullptr;
        size_ = 0;
    }

    bool empty() const { return size_ == 0; }
    size_t size() const { return size_; }

    iterator begin() { return iterator(head); }
    iterator end() { return iterator(nullptr); }

    class const_iterator {
        friend class List;
    private:
        const Node* ptr;
        explicit const_iterator(const Node* n) : ptr(n) {}
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;

        const_iterator() : ptr(nullptr) {}
        const_iterator(const const_iterator& other) : ptr(other.ptr) {}
        const_iterator(const iterator& other) : ptr(other.ptr) {}

        reference operator*() const { return ptr->data; }
        pointer operator->() const { return &(ptr->data); }

        const_iterator& operator++() { 
            if (ptr) ptr = ptr->next;
            return *this;
        }
        const_iterator operator++(int) { 
            const_iterator tmp = *this;
            ++(*this);
            return tmp;
        }
        const_iterator& operator--() { 
            if (ptr) ptr = ptr->prev;
            return *this;
        }
        const_iterator operator--(int) { 
            const_iterator tmp = *this;
            --(*this);
            return tmp;
        }
        bool operator==(const const_iterator& other) const { return ptr == other.ptr; }
        bool operator!=(const const_iterator& other) const { return ptr != other.ptr; }
    };
    const_iterator begin() const { return const_iterator(head); }
    const_iterator end() const { return const_iterator(nullptr); }
};
