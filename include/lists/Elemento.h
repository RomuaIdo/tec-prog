#ifndef ELEMENTO_H
#define ELEMENTO_H

template<class TIPO>
class Elemento {
private:
    TIPO* pInfo;
    Elemento<TIPO>* pProximo;
    Elemento<TIPO>* pAnterior;

public:
    Elemento();
    Elemento(TIPO* info);
    ~Elemento();

    TIPO* getInfo() const;

    void setInfo(TIPO* info);

    Elemento<TIPO>* getProximo();

    void setProximo(Elemento<TIPO>* proximo);

    Elemento<TIPO>* getAnterior() const;

    void setAnterior(Elemento<TIPO>* anterior);
};

template<class TIPO>
Elemento<TIPO>::Elemento() : pInfo(nullptr), pProximo(nullptr), pAnterior(nullptr) {}

template<class TIPO>
Elemento<TIPO>::Elemento(TIPO* info) : pInfo(info), pProximo(nullptr), pAnterior(nullptr) {}

template<class TIPO>
Elemento<TIPO>::~Elemento() {
    delete pInfo;
}

template<class TIPO>
TIPO* Elemento<TIPO>::getInfo() const {
    return pInfo;
}

template<class TIPO>
void Elemento<TIPO>::setInfo(TIPO* info) {
    pInfo = info;
}

template<class TIPO>
Elemento<TIPO>* Elemento<TIPO>::getProximo() {
    return pProximo;
}

template<class TIPO>
void Elemento<TIPO>::setProximo(Elemento<TIPO>* proximo) {
    pProximo = proximo;
}

template<class TIPO>
Elemento<TIPO>* Elemento<TIPO>::getAnterior() const {
    return pAnterior;
}

template<class TIPO>
void Elemento<TIPO>::setAnterior(Elemento<TIPO>* anterior) {
    pAnterior = anterior;
}


#endif
