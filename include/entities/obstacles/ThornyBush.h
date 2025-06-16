#ifndef THORNY_BUSH_H
#define THORNY_BUSH_H
#include "../characters/Player.h"
#include "../characters/Enemy.h"
#include "Obstacle.h"

class ThornyBush : public Obstacle {

private:
  /* ------ STATUS ------- */
  int spikes; // Number of spikes in the bush
  float time_between_attacks;
  float own_clock;
  Texture texture_hide;
  Texture texture_spikes;
  bool is_active; // Whether the bush is currently active or not

public:
  ThornyBush(float x, float baseY, bool harm = true);
  ~ThornyBush();

  /* ---- OWN FUNCTIONS ---- */
  void obstacleAction(Entity *e);
  void execute();
  void collide(Entity *e);
  void dealDamage(Player *p);
  void setState();
  void update();

  /* ----- GETS & SETS ----- */
  void setSpikes(int s = 2);
  int getSpikes() const;
};


#endif
