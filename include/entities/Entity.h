#ifndef ENTITY_H
#define ENTITY_H
#include "Ente.h"

class Entity : public Ente {
public:
  Entity();
  virtual ~Entity();

  virtual void execute() = 0;
  virtual void draw() = 0;
  virtual void update() = 0;
  virtual void collide() = 0;
};
#endif
