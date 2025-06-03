#ifndef FASE_H
#define FASE_H
#include "../entities/Ente.h"
#include "../entities/Entity.h"

class Phase : public Ente {
protected:
  //Lista<Entity*> entities;
  //CollisionManager* collisions_manager;

public:
  Phase();
  ~Phase();

  virtual void execute() = 0;

}

#endif
