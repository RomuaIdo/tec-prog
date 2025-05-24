#ifndef ENTIDADE_H
#define ENTIDADE_H
#include "Ente.h"

class Entidade : public Ente {
public:
  Entidade();
  virtual ~Entidade();

  virtual void executar() = 0;
  virtual void desenhar() = 0;
  virtual void atualizar() = 0;

  virtual void colidir() = 0;
};
#endif
