#ifndef FASE_H
#define FASE_H
#include "../entities/Ente.h"
#include "../entities/Entity.h"

class Fase : public Ente {
protected:
  Lista<Entity*> entities;
  CollisionManager* collisions_manager;

public:
  Fase();
  ~Fase();

  virtual void execute() = 0;

}

#endif
