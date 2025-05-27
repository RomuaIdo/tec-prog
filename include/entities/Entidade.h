#ifndef ENTITY_H
#define ENTITY_H
#include "Ente.h"

class Entitye : public Ente {
public:
  Entity();
  virtual ~Entity();

  virtual void execute() = 0;
  virtual void draw() = 0;
  virtual void update() = 0;
  virtual void colide() = 0;
};
#endif
