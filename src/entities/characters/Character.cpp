#include "../../../include/entities/characters/Character.h"
#include <SFML/Window.hpp>

Vector2f Character::gravity(0.f, 30.f);

Character::Character()
    : Entity(), health(5), strength(1), aceleration(0.f), velocity(0.f, 0.f),
      in_air(true), friction(0.f, 0.f), friction_coef(0.5f) {
  centerOrigin();
}

Character::Character(float x, float y, const float movSpeed, int life,
                     float coef, int s)
    : Entity(x, y), health(life), strength(s), aceleration(movSpeed),
      velocity(0.f, 0.f), in_air(true), friction(0.f, 0.f),
      friction_coef(coef) {
  centerOrigin();
}

Character::~Character() {}

/* ------------------------------------------- */
/*                OWN FUNCTIONS                */
/* ------------------------------------------- */

void Character::moveCharacter() {
  if (in_air) {
    velocity.y += gravity.y * pGM->getdt();
  }

  position += velocity;
  sprite.setPosition(position);
  in_air = true; // Reset for the next frame
}

/* ------------------------------------------- */
/*                 GETS & SETS                 */
/* ------------------------------------------- */

Vector2f Character::getVelocity() const { return velocity; }

void Character::setVelocity(Vector2f vel) { velocity = vel; }

void Character::setInAir(bool inair) { in_air = inair; }

bool Character::isInAir() const { return in_air; }
