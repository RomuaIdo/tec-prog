#ifndef ITERATOR_H
#define ITERATOR_H

#include "Element.h"
#include <iterator>

template <typename T> class List;
template <typename T> class ListIterator;
template <typename T> class ConstListIterator;

// Iterador regular (mutable)
template <typename T> class ListIterator {
public:
  //typedef T *pointer;
  //typedef T &reference;


  ListIterator() : ptr(0) {}
  ListIterator(const ListIterator &other) : ptr(other.ptr) {}
  ~ListIterator() {}

  T& operator*() const { return ptr->data; }
  T* operator->() const { return &(ptr->data); }

  ListIterator &operator++() {
    if (ptr)
      ptr = ptr->next;
    return *this;
  }

  ListIterator operator++(int) {
    ListIterator tmp = *this;
    ++(*this);
    return tmp;
  }

  ListIterator &operator--() {
    if (ptr)
      ptr = ptr->prev;
    return *this;
  }

  ListIterator operator--(int) {
    ListIterator tmp = *this;
    --(*this);
    return tmp;
  }

  ListIterator &operator=(const ListIterator &other) {
    ptr = other.ptr;
    return *this;
  }

  bool operator==(const ListIterator &other) const { return ptr == other.ptr; }
  bool operator!=(const ListIterator &other) const { return ptr != other.ptr; }

private:
  friend class List<T>;
  explicit ListIterator(Node<T> *n) : ptr(n) {}
  Node<T> *ptr;
};





/*
// const_iterator (read-only)
template <typename T> class ConstListIterator {
public:
  //typedef const T *pointer;
  //typedef const T &reference;

  ConstListIterator() : ptr(0) {}
  ~ConstListIterator() {}
  ConstListIterator(const ConstListIterator &other) : ptr(other.ptr) {}
  ConstListIterator(const ListIterator<T> &other) : ptr(other.ptr) {}

  T& operator*() const { return ptr->data; }
  T* operator->() const { return &(ptr->data); }

  ConstListIterator &operator++() {
    if (ptr)
      ptr = ptr->next;
    return *this;
  }

  ConstListIterator operator++(int) {
    ConstListIterator tmp = *this;
    ++(*this);
    return tmp;
  }

  ConstListIterator &operator--() {
    if (ptr)
      ptr = ptr->prev;
    return *this;
  }

  ConstListIterator operator--(int) {
    ConstListIterator tmp = *this;
    --(*this);
    return tmp;
  }

  ConstListIterator &operator=(const ConstListIterator &other) {
    ptr = other.ptr;
    return *this;
  }

  bool operator==(const ConstListIterator &other) const {
    return ptr == other.ptr;
  }
  bool operator!=(const ConstListIterator &other) const {
    return ptr != other.ptr;
  }

private:
  friend class List<T>;
  explicit ConstListIterator(const Node<T> *n) : ptr(n) {}
  const Node<T> *ptr;
};
*/
#endif
