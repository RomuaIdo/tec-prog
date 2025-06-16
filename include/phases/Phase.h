#ifndef FASE_H
#define FASE_H

#include "../entities/Ente.h"
#include "../entities/Entity.h"
#include "../lists/EntitiesList.h"
#include "../managers/CollisionManager.h"

class Tile;

class Phase : public Ente {
protected:
  EntitiesList entities_list;
  vector<Tile *> tiles;
  CollisionManager *pCM;
  Vector2f phaseSize;
  Player *player1;
  Player *player2;
  short int maxPlatforms;

public:
  Phase(Vector2f size, Player *p1, Player *p2, const string &backgroundPath);
  virtual ~Phase();

  virtual void execute() = 0;
  virtual void createEnemies() = 0;
  virtual void createObstacles() = 0;
  void createPlatforms();
  void createScenery();

  Vector2f getPhaseSize() const;
};

#endif
