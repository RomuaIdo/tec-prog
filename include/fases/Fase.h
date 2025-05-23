#ifndef FASE_H
#define FASE_H
#include "../entidades/Ente.h"
#include "../entidades/Entidade.h"

class Fase : public Ente {
protected:
  Lista<Entidade*> entidades;
  Gerenciador_Colisoes* gerenciadorColisoes;

public:
  Fase();
  ~Fase();

  virtual void executar() = 0;

}

#endif
