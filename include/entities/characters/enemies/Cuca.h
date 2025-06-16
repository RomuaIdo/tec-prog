#ifndef CUCA_H
#define CUCA_H
#include "../../Projectile.h"
#include "../Enemy.h"
#include <SFML/Graphics.hpp>
#include <list>
#include <math.h>

enum class CucaState { IDLE, MOVING_LEFT, MOVING_RIGHT };

class Cuca : public Enemy {

protected:
  list<Projectile *> potions;
  float makingPotion;
  float clock;
  CucaState currentState;
  float stateTimer;
  const float STATE_DURATION = 2.0f; // Tempo em cada estado

public:
  Cuca(float x, float y, const float acel = 10.f, int life = 5,
       float coef = 0.5, int s = 1);
  ~Cuca();

  /* ---- OWN FUNCTIONS ---- */
  void execute();
  void move();
  void collide(Entity *e);

  /* ---- POTIONS ---- */
  void makePotion();
  void throwPotion();
  void addPotion(Projectile *pot);

  /* ------- PLAYER -------- */

  void attack(Player *p);
};

#endif
