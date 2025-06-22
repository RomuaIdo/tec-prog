#include "../../../include/entities/characters/Character.h"
#include <SFML/Window.hpp>

Character::Character()
    :Entity(), aceleration(0.f), health(1), alive(true), strength(1),
    takeDamageClock(0.f), damageBlinkClock(0.f), isBlinking(false), 
    friction(0.f,0.f), faced_right(1){

}

Character::Character(float x, float y, float acel, int life, int s)
    : Entity(x, y), aceleration(acel), health(life), alive(true), strength(s),
      takeDamageClock(0.f), damageBlinkClock(0.f), isBlinking(false),
      friction(0.f, 0.f), faced_right(1), in_air(true) {}

Character::~Character() {}

/* ------------------------------------------- */
/*                OWN FUNCTIONS                */
/* ------------------------------------------- */

void Character::moveCharacter() {
  position += velocity;

  // Flip sprite based on direction
  if (faced_right == -1) {
    sprite.setScale(-1.f, 1.f); // Facing left
  } else {
    sprite.setScale(1.f, 1.f); // Facing right
  }
  setPosition(position);
}

void Character::takeDamage(int damage, int direction) {
    if (health - damage <= 0) {
        health = 0;
        alive = false;
    } else {
        health -= damage;
        velocity.x = direction * XPUSH;
        velocity.y = -YPUSH;
        moveCharacter();

        isBlinking = true;
        damageBlinkClock = 0.f;
    }
}

void Character::updateDamageBlink() {
    if (isBlinking) {
        damageBlinkClock += pGM->getdt();

        // Alterna opacidade
        if (static_cast<int>(damageBlinkClock * 10) % 2 == 0) {
            sprite.setColor(sf::Color(255, 255, 255, 100)); // transparente
        } else {
            sprite.setColor(sf::Color(255, 255, 255, 255)); // normal
        }

        // Para de piscar após 1 segundo
        if (damageBlinkClock >= 1.0f) {
            isBlinking = false;
            damageBlinkClock = 0.f;
            sprite.setColor(sf::Color(255, 255, 255, 255)); // reset
        }
    }
}

void Character::applyFriction(float dt) {
  if (velocity.x > 0) {
    friction.x = -FRICTION;
    if (velocity.x + friction.x * dt < 0) {
      velocity.x = 0;
      friction.x = 0; // Stop friction when velocity is zero
    }
  } else if (velocity.x < 0) {
    friction.x = FRICTION;
    if (velocity.x + friction.x * dt > 0) {
      velocity.x = 0;
      friction.x = 0; // Stop friction when velocity is zero
    }
  } else {
    friction.x = 0;
  }
  velocity += friction * dt;
}

/* ------------------------------------------- */
/*                 GETS & SETS                 */
/* ------------------------------------------- */

int Character::getHealth() const { return health; }

int Character::getStrength() const { return strength; }

bool Character::getInAir() const { return in_air; }

void Character::setInAir(bool inAir) { in_air = inAir; }

bool Character::getAlive() const { return alive; }
