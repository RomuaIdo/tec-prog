#include "../../../../include/entities/characters/enemies/Cuca.h"
#include "../../../../include/entities/characters/Player.h"
#include "../../../../include/managers/CollisionManager.h"

Cuca::Cuca(float x, float y, const float acel, int life, float coef, int s)
    : Enemy(x, y, acel, life, coef, s), makingPotion(0.f),
      currentState(CucaState::IDLE), stateTimer(0.0f) {

  if (!texture.loadFromFile("assets/textures/Cuca.png")) {
    std::cerr << "Failed to load Cuca.png!" << std::endl;
  }
  texture.setSmooth(true);
  sprite.setTexture(texture);
  centerOrigin();

  // CORREÇÃO: Ajustar tamanho após carregar textura
  size.x = sprite.getLocalBounds().width;
  size.y = sprite.getLocalBounds().height;
  sprite.setScale(size.x / sprite.getLocalBounds().width,
                  size.y / sprite.getLocalBounds().height);
  velocity = Vector2f(0.f, 0.f);
  faced_right = true;
}

Cuca::~Cuca() {}

/* ------------------------------------------- */
/*                OWN FUNCTIONS                */
/* ------------------------------------------- */

void Cuca::execute() {
  move();
  draw();
  makePotion();
  throwPotion();
}

void Cuca::move() {
  stateTimer += pGM->getdt();

  // Transição de estados após 2 segundos
  if (stateTimer >= STATE_DURATION) {
    stateTimer = 0.0f;

    switch (currentState) {
    case CucaState::IDLE:
      // Alterna entre esquerda e direita após pausa
      currentState =
          (rand() % 2 == 0) ? CucaState::MOVING_LEFT : CucaState::MOVING_RIGHT;
      break;

    case CucaState::MOVING_LEFT:
    case CucaState::MOVING_RIGHT:
      // Volta para estado de pausa
      currentState = CucaState::IDLE;
      velocity.x = 0.0f; // Para completamente
      break;
    }
  }

  // Executa ações baseadas no estado atual
  switch (currentState) {
  case CucaState::MOVING_LEFT:
    velocity.x = -aceleration;
    faced_right = false;
    break;

  case CucaState::MOVING_RIGHT:
    velocity.x = aceleration;
    faced_right = true;
    break;

  case CucaState::IDLE:
    // Nada a fazer, já está parado
    break;
  }

  // Aplica movimento e gravidade
  moveCharacter();
}

void Cuca::collide(Entity *e) {

  // If the entity is a Player, attack it
  if (dynamic_cast<Player *>(e)) {
    Player *p = static_cast<Player *>(e);
    if (p) {
      attack(p);
    }
  }
}

/* ------------------------------------------- */
/*              POTIONS FUNCTIONS              */
/* ------------------------------------------- */

void Cuca::makePotion() {
  if (makingPotion >= 1.f) {
    Projectile *potion =
        new Projectile(position.x + (faced_right * (10.f + size.x)), position.y,
                       faced_right * 10.f);

    if (potion) {
      Texture potionTexture;
      if (potionTexture.loadFromFile("assets/textures/Potion.png")) {
        potion->setTexture(potionTexture);
      } else {
        std::cerr << "Failed to load Potion.png!" << std::endl;
        delete potion; // CORREÇÃO: Liberar memória se falhar
        makingPotion = 0.f;
        return;
      }

      addPotion(potion);
      CollisionManager::getInstance()->addProjectile(potion);
    }
    makingPotion = 0.f;
  }
  makingPotion += pGM->getdt();
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

/* ------------------------------------------- */
/*              PLAYER FUNCTIONS               */
/* ------------------------------------------- */

void Cuca::attack(Player *p) {
  /* If player has health and after 2 seconds, then he can attack */
  if (p->getHealth() > 0 && pGM->getClockTime() >= 2.f) {
    p->loseHealth(strength);
    pGM->resetClock();
  }
}
