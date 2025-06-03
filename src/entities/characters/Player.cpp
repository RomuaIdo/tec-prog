#include "../../../include/entities/characters/Player.h"
#include <SFML/Window.hpp>

Player::Player(float x, float y, const float acel, int life, float coef, int s,
               int p_num, const float v_max)
    : Character(x, y, acel, life, coef, s), projectiles_list(),
      player_num(p_num), score(0), vel_max(v_max) {
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

float modulee(float x) {
  if (x < 0)
    return -x;
  return x;
}

void Player::shoot() {
    if (player_num == 1) {
        if (Keyboard::isKeyPressed(sf::Keyboard::C)) {
            Vector2f velocity = getVelocity();
            float dirX = (velocity.x != 0) ? velocity.x / modulee(velocity.x) : 1.f;
            
            Projectile *p = new Projectile(position.x, position.y, dirX * 10.f);
            if (p) {
                addProjectile(p);
            } else {
                cout << "Projectile not allocated." << endl;
            }
        }
    }
}

void Player::addProjectile(Projectile *p) { projectiles_list.push_back(p); }

void Player::move() {

  if (player_num == 1) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
      if (isOnGround()) {
        speed.y += -(15);
        setOnGround(false);
      }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
      speed.x += -aceleration * pGM->getdt();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
      speed.x += aceleration * pGM->getdt();
  } else {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
      if (isOnGround()) {
        speed.y += -(15);
        setOnGround(false);
      } 
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
      speed.x += -aceleration * pGM->getdt();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
      speed.x += aceleration * pGM->getdt();
  }

  const float vel_max = 15.f;

  // See if velocity ultrapassed vel_max
  if (speed.x > vel_max) {
    speed.x = vel_max;
  }
  if (speed.x < -vel_max) {
    speed.x = -vel_max;
  }

  // Apply friction
  if (speed.x > 0) {
    friction.x = -20.f * friction_coef;
    if (speed.x + friction.x * pGM->getdt() < 0) {
      speed.x = 0;
      friction.x = 0;
    }
  } else if (speed.x < 0) {
    friction.x = 20.f * friction_coef;
    if (speed.x + friction.x * pGM->getdt() > 0) {
      speed.x = 0;
      friction.x = 0;
    }
  } else
    friction.x = 0;

  speed += friction * pGM->getdt();
  moveCharacter();
}

void Player::collide() { speed = Vector2f(speed.x * -0.1f, speed.y * -0.1f); }

void Player::execute() {
  move();
  draw();
  shoot();
  for (list<Projectile *>::iterator it = projectiles_list.begin();
       it != projectiles_list.end(); it++) {
    if (*it)
      // if((*it)->getActive()){
      //     (*it)->execute();
      // }else
      //     delete (*it);
      (*it)->execute();
  }
}

void Player::loseHealth(int damage) { health -= damage; }

int Player::getHealth() { return health; }
