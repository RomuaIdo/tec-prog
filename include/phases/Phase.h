#ifndef FASE_H
#define FASE_H

#include "../entities/Ente.h"
#include "../entities/Entity.h"
#include "../lists/EntitiesList.h"
#include "../managers/CollisionManager.h"

class Phase : public Ente {
protected:
  EntitiesList entities_list;
  CollisionManager *pCM;
  Vector2f phaseSize;
  Player *player1;
  Player *player2;

public:
  Phase(Vector2f size, Player *p1, Player *p2);
  virtual ~Phase();

  virtual void execute() = 0;
  virtual void createEnemies() = 0;
  virtual void createObstacles() = 0;
  virtual void createPlatforms() = 0;
  virtual void createScenery() = 0;

  Vector2f getPhaseSize() const;
};

#endif
