#include "../../../../include/entities/characters/enemies/Cuca.h"
#include "../../../../include/managers/CollisionManager.h"

Cuca::Cuca() : Enemy(), potionClock(0.f) {
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
    updateDamageBlink();
  }
  throwPotion();
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


void Cuca::updateClocks() {
  float dt = pGM->getdt();

  clock += dt;
  potionClock += dt;
}

/* ------------------------------------------- */
/*                 SAVE BUFFER                 */
/* ------------------------------------------- */

json Cuca::toJson() const {
  json j;
  j["type"] = getType();
  j["position_x"] = position.x;
  j["position_y"] = position.y;
  j["health"] = health;
  j["potionClock"] = potionClock;
  j["faced_right"] = faced_right;
  j["aceleration"] = aceleration;
  j["strength"] = strength;
  j["evilness"] = evilness;
  j["alive"] = alive;
  j["takeDamageClock"] = takeDamageClock;
  j["clock"] = clock;
  j["damageBlinkClock"] = damageBlinkClock;
  j["isBlinking"] = isBlinking;

  vector<json> potions_json;

  list<Projectile *>::const_iterator it;
  for (it = potions.begin(); it != potions.end(); ++it) {
    if (*it) {
      potions_json.push_back((*it)->toJson());
    }
  }
  j["potions"] = potions_json;
  return j;
}

void Cuca::fromJson(const json &j) {
  position.x = j.at("position_x");
  position.y = j.at("position_y");
  health = j.at("health");
  potionClock = j.at("potionClock");
  faced_right = j.at("faced_right");
  evilness = j.at("evilness");
  aceleration = j.at("aceleration");
  strength = j.at("strength");
  alive = j.at("alive");
  takeDamageClock = j.at("takeDamageClock");
  clock = j.at("clock");
  damageBlinkClock = j.at("damageBlinkClock");
  isBlinking = j.at("isBlinking");
  // Clear the existing projectiles list
  for (list<Projectile *>::iterator it = potions.begin();
       it != potions.end(); it++) {
    if (*it) {
      delete (*it);
      (*it) = nullptr;
    }
  }
  potions.clear();
  // Load projectiles from JSON
  if (j.contains("potions")) {
    for (const auto &proj_json : j.at("potions")) {
      Projectile *p = new Projectile();
      p->setOwner(this);
      p->fromJson(proj_json);
      addPotion(p);
    }
  }
}

std::string Cuca::getType() const { return "Cuca"; }

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

void Cuca::addPotion(Projectile *pot) {
  if (pot) {
    potions.push_back(pot);
    CollisionManager::getInstance()->addProjectile(pot);
  } else {
    cerr << "Failed to add potion: null pointer" << endl;
  }
}
