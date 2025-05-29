#ifndef ITERADOR_H
#define ITERADOR_H
#include "Elemento.h"

template <class TIPO> 
class iterador {
private:
  Elemento<TIPO> *pAtual;

public:
  iterador();
  iterador(Elemento<TIPO> *atual);
  ~iterador();

  Elemento<TIPO> *getAtual() const;
  void setAtual(Elemento<TIPO> *atual);

  bool operator==(const iterador<TIPO> &outro) const;
  bool operator!=(const iterador<TIPO> &outro) const;

  TIPO *operator*() const;
  iterador<TIPO> &operator++();
  iterador<TIPO> &operator--();
};

template <class TIPO> iterador<TIPO>::iterador() : pAtual(nullptr) {}

template <class TIPO>
iterador<TIPO>::iterador(Elemento<TIPO> *atual) : pAtual(atual) {}

template <class TIPO> iterador<TIPO>::~iterador() { pAtual = nullptr; }

template <class TIPO> Elemento<TIPO> *iterador<TIPO>::getAtual() const {
  return pAtual;
}

template <class TIPO> void iterador<TIPO>::setAtual(Elemento<TIPO> *atual) {
  pAtual = atual;
}

template <class TIPO>
bool iterador<TIPO>::operator==(const iterador<TIPO> &outro) const {
  return pAtual == outro.pAtual;
}

template <class TIPO>
bool iterador<TIPO>::operator!=(const iterador<TIPO> &outro) const {
  return pAtual != outro.pAtual;
}

template <class TIPO> TIPO *iterador<TIPO>::operator*() const {
  return pAtual->getInfo();
}

template <class TIPO> iterador<TIPO> &iterador<TIPO>::operator++() {
  if (pAtual != nullptr) {
    pAtual = pAtual->getProximo();
  }
  return *this;
}

template <class TIPO> iterador<TIPO> &iterador<TIPO>::operator--() {
  if (pAtual != nullptr) {
    pAtual = pAtual->getAnterior();
  }
  return *this;
}

#endif
