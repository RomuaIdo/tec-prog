#include "../../../include/entities/characters/Player.h"
#include "../../../include/managers/CollisionManager.h"
#include <SFML/Window.hpp>


Player::Player()
    : Character(), player_num(1), score(0), vel_max(50.f), projectiles_list(),
      shoot_delay(0.f) {
  projectiles_list.clear();

  if (!texture.loadFromFile("assets/textures/Player1Sprite.png")) {
    std::cerr << "Failed to load PlayerSprite.png!" << std::endl;
  }

  texture.setSmooth(true);
  sprite.setTexture(texture);
  centerOrigin();
  size.x = sprite.getLocalBounds().width;
  size.y = sprite.getLocalBounds().height;
  sprite.setScale(size.x / sprite.getLocalBounds().width,
                  size.y / sprite.getLocalBounds().height);
}

Player::Player(float x, float y, const float acel, int life, float coef, int s,
               int p_num, const float v_max)
    : Character(x, y, acel, life, coef, s), player_num(p_num), score(0),
      vel_max(v_max), projectiles_list(), shoot_delay(0.f) {
  projectiles_list.clear();

  if (p_num == 1) {
    if (!texture.loadFromFile("assets/textures/Player1Sprite.png")) {
      std::cerr << "Failed to load PlayerSprite.png!" << std::endl;
    }
  } else {
    if (!texture.loadFromFile("assets/textures/Player2Sprite.png")) {
      std::cerr << "Failed to load PlayerSprite.png!" << std::endl;
    }
  }

  texture.setSmooth(true);
  sprite.setTexture(texture);
  centerOrigin();
  size.x = sprite.getLocalBounds().width;
  size.y = sprite.getLocalBounds().height;
  sprite.setScale(size.x / sprite.getLocalBounds().width,
                  size.y / sprite.getLocalBounds().height);
}

Player::~Player() {
  for (list<Projectile *>::iterator it = projectiles_list.begin();
       it != projectiles_list.end(); it++) {
    if (*it) {
      delete (*it);
      (*it) = nullptr;
    }
  }
  projectiles_list.clear();
}

/* ------------------------------------------- */
/*                OWN FUNCTIONS                */
/* ------------------------------------------- */

void Player::move() {
  Ente::setGraphicsManager(GraphicsManager::getInstance());
  const float dt = pGM->getdt();
  const float jumpForce = 15.0f;
  const float maxVel = 15.0f;

  if (player_num == 1) {
    handlePlayer1Controls(dt, jumpForce);
  } else {
    handlePlayer2Controls(dt, jumpForce);
  }

  // Limits for the horizontal velocity
  if (velocity.x > maxVel)
    velocity.x = maxVel;
  if (velocity.x < -maxVel)
    velocity.x = -maxVel;

  applyFriction(dt);
  moveCharacter();
}

void Player::handlePlayer1Controls(float dt, float jumpForce) {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
    if (!isInAir()) {
      velocity.y = -jumpForce;
      setInAir(true);
    }
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
    velocity.x -= aceleration * dt;
    faced_right = false;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
    velocity.x += aceleration * dt;
    faced_right = true;
  }
}

void Player::handlePlayer2Controls(float dt, float jumpForce) {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
    if (!isInAir()) {
      velocity.y = -jumpForce;
      setInAir(true);
    }
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    velocity.x -= aceleration * dt;
    faced_right = false;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
    velocity.x += aceleration * dt;
    faced_right = true;
  }
}

void Player::applyFriction(float dt) {
  if (velocity.x > 0) {
    friction.x = -20.0f * friction_coef;
    if (velocity.x + friction.x * dt < 0) {
      velocity.x = 0;
    }
  } else if (velocity.x < 0) {
    friction.x = 20.0f * friction_coef;
    if (velocity.x + friction.x * dt > 0) {
      velocity.x = 0;
    }
  } else {
    friction.x = 0;
  }
  velocity += friction * dt;
}

void Player::execute() {
  move();
  draw();
  shoot();

  std::list<Projectile *>::iterator it = projectiles_list.begin();
  while (it != projectiles_list.end()) {
    Projectile *p = *it;
    if (p && p->getActive()) {
      p->execute();
      ++it;
    } else {
      // Remove from CollisionManager before deleting
      CollisionManager::getInstance()->removeProjectile(p);

      delete p; // Delete the projectile
      it = projectiles_list.erase(it);
    }
  }
}

void Player::loseHealth(int damage) { health -= damage; }

/* ------------------------------------------- */
/*                GUN FUNCTIONS                */
/* ------------------------------------------- */

void Player::shoot() {
  if (player_num == 1) {

    if (Keyboard::isKeyPressed(sf::Keyboard::C)) {
      if (shoot_delay >= 0.5f) {
        // Determine the direction based on facing
        float direction = faced_right ? 1.0f : -1.0f;
        Projectile *p = new Projectile(
            position.x + (faced_right ? size.x : 0), position.y + size.y / 2,
            direction * 10.f // Velocity with direction
        );

        if (p) {
          addProjectile(p);
          CollisionManager::getInstance()->addProjectile(
              p); // Register the projectile in the CollisionManager
        }
        shoot_delay = 0.f;
      }
    }
  }
  reload();
}
/*
void Player::shootProjectiles() {
  for (list<Projectile *>::iterator it = projectiles_list.begin();
       it != projectiles_list.end(); it++) {
    if (*it) {
      if (!(*it)->getActive()) {
        // delete (*it); // essa porra da seg fault
        (*it) = nullptr;
        it = projectiles_list.erase(it);
        if (it == projectiles_list.end())
          break;
      } else
        (*it)->execute();
    }
  }
}
*/
void Player::addProjectile(Projectile *p) { projectiles_list.push_back(p); }

void Player::reload() { shoot_delay += pGM->getdt(); }

/* ------------------------------------------- */
/*                 GETS & SETS                 */
/* ------------------------------------------- */

int Player::getHealth() { return health; }
