#ifndef OBSTACLE_H
#define OBSTACLE_H
#include "../Entity.h"
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class Player;
class Enemy;

class Obstacle : public Entity {

protected:
  /* ------ STATUS ------- */
  bool harmful;

public:
  Obstacle();
  Obstacle(bool harm, float x, float y);
  virtual ~Obstacle();

  // virtual void dealDamage() = 0;

  /* ---- OWN FUNCTIONS ---- */
  virtual void collide(Entity *other) = 0;
  virtual void execute() = 0;
  virtual void obstacleAction(Player *player) = 0;
  virtual void obstacleAction(Enemy* enemy) = 0;
};

#endif
