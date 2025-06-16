#include "../../../include/entities/obstacles/Honey.h"

Honey::Honey(float x, float y, bool harm, const string &texturePath)
    : Obstacle(harm, x, y), viscosity(0.6f) {
  if (!texture.loadFromFile(texturePath)) {
    cerr << "Failed to load Honey.png!" << endl;
  }
  sprite.setTexture(texture);
  sprite.setPosition(x, y);
  size =
      Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
  centerOrigin();
}

Honey::~Honey() {}

/* ------------------------------------------- */
/*                OWN FUNCTIONS                */
/* ------------------------------------------- */

void Honey::execute() { draw(); }

void Honey::obstacleAction(Player *p) {
  if (p) {
    Vector2f velocity = p->getSpeed();
    velocity.x *= viscosity;          // Slow down the character's speed
    velocity.y *= (viscosity + 0.2f); // Slow down the character's jump
    p->setSpeed(velocity);
  }
}

void Honey::obstacleAction(Enemy *e) {
  if (e) {
    Vector2f velocity = e->getSpeed();
    velocity.x *= viscosity;          // Slow down the enemy's speed
    velocity.y *= (viscosity + 0.2f); // Slow down the enemy's jump
    e->setSpeed(velocity);
  }
}

void Honey::collide(Entity *e) {
  if (e) {
    if (Player *p = dynamic_cast<Player *>(e)) {
      obstacleAction(p);
    } else if (Enemy *en = dynamic_cast<Enemy *>(e)) {
      obstacleAction(en);
    }
  }
}

/* ------------------------------------------- */
/*                 GETS & SETS                 */
/* ------------------------------------------- */

void Honey::setViscosity(float v) { viscosity = v; }

float Honey::getViscosity() const { return viscosity; }
