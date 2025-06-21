#include "../../../../include/entities/characters/enemies/Cuca.h"
#include "../../../../include/managers/CollisionManager.h"


Cuca::Cuca()
    : Enemy(), potionClock(0.f){
    texture = pGM->loadTexture("assets/textures/Cuca.png");
    sprite.setTexture(texture);
    configSprite();

    evilness = CUCAEVILNESS;
}


Cuca::Cuca(float x, float y, const float acel, int life, int s)
    : Enemy(x, y, acel, life, s), potionClock(0.f) {


    velocity = Vector2f(faced_right * aceleration, 0.f);
    texture = pGM->loadTexture("assets/textures/Cuca.png");
    sprite.setTexture(texture);
    configSprite();
    evilness = CUCAEVILNESS;

}

Cuca::~Cuca() {}

/* ------------------------------------------- */
/*                OWN FUNCTIONS                */
/* ------------------------------------------- */

void Cuca::execute() {
  if (alive) {
    move();
    draw();
    makePotion();
    verifyDeadPlayers();
    updateClocks();
    throwPotion();
    updateDamageBlink();
  } 
}

void Cuca::move() {

    // Change direction after 2 seconds
    if (clock > 2.f) {
        faced_right *= -1;
        clock = 0;
        velocity.x = faced_right * (aceleration);
    }
    applyGravity();
    moveCharacter();
}

/* ------------------------------------------- */
/*              POTIONS FUNCTIONS              */
/* ------------------------------------------- */

void Cuca::makePotion() {
  // Delay to throw potion
  if (potionClock >= POTIONCOOLDOWN) {
    Projectile *p =
        new Projectile(position.x + (faced_right * size.x), position.y - size.y,
                       Vector2f(faced_right * POTIONACEL, -10.f), this);

    if (p) {
      p->configSprite();
      addPotion(p);
      CollisionManager::getInstance()->addProjectile(p);

    } else
      cout << "Potion not allocated" << endl;

    potionClock = 0.f;
  }
}

void Cuca::throwPotion() {
  list<Projectile *>::iterator it = potions.begin();
  while (it != potions.end()) {
    Projectile *p = *it;
    if (p && p->getActive()) {
      p->execute();
      ++it;
    } else {
      // Remove from CollisionManager before deleting
      CollisionManager::getInstance()->removeProjectile(p);

      // Delete the projectile
      delete p;
      it = potions.erase(it);
    }
  }
}

void Cuca::addPotion(Projectile *pot) { potions.push_back(pot); }

void Cuca::updateClocks() {
  float dt = pGM->getdt();

  clock += dt;
  potionClock += dt;
}

/* ------------------------------------------- */
/*                 SAVE BUFFER                 */
/* ------------------------------------------- */

json Cuca::toJson() const {
    return {
        {"type", getType()},
        {"position_x", position.x},
        {"position_y", position.y},
        {"health", health},
        {"potionClock", potionClock}
    };
}

void Cuca::fromJson(const json& j) {
    position.x = j.at("position_x");
    position.y = j.at("position_y");
    health = j.at("health");
    potionClock = j.at("potionClock");
}

std::string Cuca::getType() const {
    return "Cuca";
}

/* ------------------------------------------- */
/*              PLAYER FUNCTIONS               */
/* ------------------------------------------- */

void Cuca::attack(Player *p) {
  /* If player has health and after 2 seconds, then he can attack */
  if (p->getHealth() > 0 && pGM->getClockTime() >= 2.f) {
    int direction = static_cast<int>(p->getPosition().x - position.x);
    direction /= abs(direction);
    p->takeDamage(strength, direction);
    pGM->resetClock();
  }
}
