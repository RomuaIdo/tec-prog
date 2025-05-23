#ifndef LISTA_H
#define LISTA_H
#include "Elemento.h"
#include "Iterador.h"

template <class TIPO> class Lista {
private:
  Elemento<TIPO> *pPrimeiro;
  Elemento<TIPO> *pFinal;
  int tamanho;

public:
  iterador<TIPO> iterator;

  Lista();
  Lista(const Lista<TIPO> &outra);
  ~Lista();

  void push_back(const TIPO &info);
  void push_front(const TIPO &info);
  void pop_back();
  void pop_front();

  iterador<TIPO> begin();
  iterador<TIPO> end();

  bool isEmpty() const;
  int size() const;
  void clear();

};

template <class TIPO>
Lista<TIPO>::Lista() : pPrimeiro(nullptr), pFinal(nullptr), tamanho(0) {
  iterator = iterador<TIPO>(pPrimeiro);
}

template <class TIPO>
Lista<TIPO>::Lista(const Lista<TIPO> &outra) : pPrimeiro(nullptr), pFinal(nullptr), tamanho(0) {
  iterator = iterador<TIPO>(pPrimeiro);
  Elemento<TIPO> *atual = outra.pPrimeiro;
  while (atual != nullptr) {
    push_back(*(atual->getInfo()));
    atual = atual->getProximo();
  }
}

template <class TIPO>
Lista<TIPO>::~Lista() {
  clear();
}

template <class TIPO>
void Lista<TIPO>::push_back(const TIPO &info) {
  Elemento<TIPO> *novoElemento = new Elemento<TIPO>(new TIPO(info));
  if (isEmpty()) {
    pPrimeiro = novoElemento;
    pFinal = novoElemento;
  } else {
    pFinal->setProximo(novoElemento);
    novoElemento->setAnterior(pFinal);
    pFinal = novoElemento;
  }
  tamanho++;
}

template <class TIPO>
void Lista<TIPO>::push_front(const TIPO &info) {
  Elemento<TIPO> *novoElemento = new Elemento<TIPO>(new TIPO(info));
  if (isEmpty()) {
    pPrimeiro = novoElemento;
    pFinal = novoElemento;
  } else {
    novoElemento->setProximo(pPrimeiro);
    pPrimeiro->setAnterior(novoElemento);
    pPrimeiro = novoElemento;
  }
  tamanho++;
}

template <class TIPO>
void Lista<TIPO>::pop_back() {
  if (!isEmpty()) {
    Elemento<TIPO> *temp = pFinal;
    pFinal = pFinal->getAnterior();
    if (pFinal != nullptr) {
      pFinal->setProximo(nullptr);
    } else {
      pPrimeiro = nullptr;
    }
    delete temp;
    tamanho--;
  }
}

template <class TIPO>
void Lista<TIPO>::pop_front() {
  if (!isEmpty()) {
    Elemento<TIPO> *temp = pPrimeiro;
    pPrimeiro = pPrimeiro->getProximo();
    if (pPrimeiro != nullptr) {
      pPrimeiro->setAnterior(nullptr);
    } else {
      pFinal = nullptr;
    }
    delete temp;
    tamanho--;
  }
}

template <class TIPO>
iterador<TIPO> Lista<TIPO>::begin() {
  return iterador<TIPO>(pPrimeiro);
}

template <class TIPO>
iterador<TIPO> Lista<TIPO>::end() {
  return iterador<TIPO>(nullptr);
}

template <class TIPO>
bool Lista<TIPO>::isEmpty() const {
  return tamanho == 0;
}

template <class TIPO>
int Lista<TIPO>::size() const {
  return tamanho;
}

template <class TIPO>
void Lista<TIPO>::clear() {
  while (!isEmpty()) {
    pop_front();
  }
}

#endif
