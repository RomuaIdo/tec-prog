#ifndef LIST_H
#define LIST_H

#include <cstddef> // for size_t

template <typename T> class List {
private:
  // Simplified Node structure
  class Node {
  public:
    T data;
    Node *next;
    Node *prev;
    Node(const T &value) : data(value), next(nullptr), prev(nullptr) {}
  };

  Node *head;
  Node *tail;
  size_t size_;

public:
  // Iterator class (simplified)
  class Iterator {
  public:
    Iterator(Node *node = nullptr) : current(node) {}

    T &operator*() { return current->data; }
    T *operator->() { return &(current->data); }

    // Pre-increment
    Iterator &operator++() {
      if (current)
        current = current->next;
      return *this;
    }

    // Post-increment
    Iterator operator++(int) {
      Iterator temp = *this;
      ++(*this);
      return temp;
    }

    // Pre-decrement
    Iterator &operator--() {
      if (current)
        current = current->prev;
      return *this;
    }

    // Post-decrement
    Iterator operator--(int) {
      Iterator temp = *this;
      --(*this);
      return temp;
    }

    bool operator==(const Iterator &other) const {
      return current == other.current;
    }
    bool operator!=(const Iterator &other) const {
      return current != other.current;
    }

    // Made public for List to simplify access
    Node *current;
  };

  List() : head(nullptr), tail(nullptr), size_(0) {}
  ~List() { clear(); }

  // Copy constructor
  List(const List &other) : head(nullptr), tail(nullptr), size_(0) {
    for (Node *n = other.head; n; n = n->next) {
      push_back(n->data);
    }
  }

  // Assignment operator
  List &operator=(const List &other) {
    if (this != &other) {
      clear();
      for (Node *n = other.head; n; n = n->next) {
        push_back(n->data);
      }
    }
    return *this;
  }

  // Add element at the end
  void push_back(const T &value) {
    Node *newNode = new Node(value);
    if (!tail) {
      head = tail = newNode;
    } else {
      tail->next = newNode;
      newNode->prev = tail;
      tail = newNode;
    }
    ++size_;
  }

  // Add element at the front
  void push_front(const T &value) {
    Node *newNode = new Node(value);
    if (!head) {
      head = tail = newNode;
    } else {
      newNode->next = head;
      head->prev = newNode;
      head = newNode;
    }
    ++size_;
  }

  // Remove the element at the iterator position
  Iterator erase(Iterator pos) {
    Node *node = pos.current;
    if (!node)
      return end();

    Iterator next(node->next);

    if (node->prev)
      node->prev->next = node->next;
    else
      head = node->next;

    if (node->next)
      node->next->prev = node->prev;
    else
      tail = node->prev;

    delete node;
    --size_;
    return next;
  }

  // Delete all elements
  void clear() {
    Node *n = head;
    while (n) {
      Node *next = n->next;
      delete n;
      n = next;
    }
    head = tail = nullptr;
    size_ = 0;
  }

  bool empty() const { return size_ == 0; }
  size_t size() const { return size_; }

  // Return iterator to the first element
  Iterator begin() { return Iterator(head); }
  // Return iterator representing the end (null pointer)
  Iterator end() { return Iterator(nullptr); }
};

#endif
