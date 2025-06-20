#include "../../../include/entities/characters/Player.h"
#include "../../../include/entities/Projectile.h"
#include "../../../include/entities/obstacles/Honey.h"
#include "../../../include/managers/CollisionManager.h"
#include <SFML/Window.hpp>

Player::Player(float x, float y, const float acel, const string Name, int life,
               int s, int p_num)
    : Character(x, y, acel, life, s), shootClock(0.f), player_num(p_num),
      score(0), name(Name), jumpForce(PLAYERJUMPFORCE), projectiles_list() {
  projectiles_list.clear();

  if (p_num == 1) {
    texture = pGM->loadTexture("assets/textures/Emilia.png");
  } else {
    texture = pGM->loadTexture("assets/textures/Player2Sprite.png");
  }
  if(name == ""){
    name = "___";
  }
  cout << "Player Name: " << name << endl;
  sprite.setTexture(texture);
  configSprite();
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

void Player::execute() {
  if (alive) {
    move();
    draw();
    shoot();
    shootProjectiles();
    updateClocks();
    updateDamageBlink();
  }
}

void Player::move() {
  const float dt = pGM->getdt();

  if (player_num == 1) {
    handlePlayer1Controls(dt);
  } else {
    handlePlayer2Controls(dt);
  }

  // Limits for the horizontal velocity
  if (velocity.x > PLAYERMAXVEL)
    velocity.x = PLAYERMAXVEL;
  if (velocity.x < -PLAYERMAXVEL)
    velocity.x = -PLAYERMAXVEL;


  applyFriction(dt);
  applyGravity();
  moveCharacter();
}

void Player::collide(Entity *e) {
  Vector2f ePos = e->getPosition();
  Vector2f eSize = e->getSize();

  float dx = (position.x - ePos.x);
  float dy = (position.y - ePos.y);
  // Vector2f variation = Vector2f(dx, dy);

  /* If dx > 0 -> a in b's right  */

  /* If dy > 0 -> a is below b    */

  /*  The intersection between a and b ,   */
  /*   if they collide, the vector will be */
  /*   negative in x and y                 */

  Vector2f intersection =
      Vector2f(abs(dx) - (size.x + eSize.x), abs(dy) - (size.y + eSize.y));

  if (intersection.x < 0.0f && intersection.y < 0.0f) {

    /* If intersection in x is less then intersection in y */
    /*  means that they are side by side                 */

    if (std::abs(intersection.x) < std::abs(intersection.y)) {

      /* To push the character the amount he is inside */
      float push = abs(intersection.x / 2.f);

      if (dx > 0) {
        position.x += push;
        setVelocity(Vector2f(0.f + push, getVelocity().y));
      } else {
        position.x -= push;
        setVelocity(Vector2f(0.f - push, getVelocity().y));
      }

      /* If intersection in y is less then intersection in x */
      /*  means that character collided in y with obstacle */
    } else {

      /* To push the character the amount he is inside */
      float push = abs(intersection.y / 2.f);

      /* player is below  */
      if (dy > 0) {

        position.y += push;

        /* player is on top */
      } else {

        if(dynamic_cast<Honey*>(e)){
            jumpForce = static_cast<Honey*>(e)->getViscosity() * PLAYERJUMPFORCE; 
        }else{
            jumpForce = PLAYERJUMPFORCE;
        }
        /* player can jump */
        setInAir(false);
        position.y -= push;
        setVelocity(Vector2f(getVelocity().x, 0.f));
      }
    }
    setPosition(position);
  }
}

void Player::updateClocks() {
  float dt = pGM->getdt();

  clock += dt;
  takeDamageClock += dt;
  shootClock += dt;
}

void Player::takeDamage(int damage, int direction) {
    if (takeDamageClock >= TAKEDAMAGECOOLDOWN) {
        if (health - damage <= 0 && alive) {
            health = 0;
            alive = false;
            cout << "Player is dead!" << endl;
        } else {
            takeDamageClock = 0.f;
            health -= damage;
        
            velocity.x = direction * XPUSH;
            velocity.y = abs(direction) * -YPUSH;
            moveCharacter();
            cout << "Lost Health:" << health << endl;


            isBlinking = true;
            damageBlinkClock = 0.f;
        }
    }
}

void Player::increaseScore(int points) {
  score += points;
}

/* ------------------------------------------- */
/*                INPUT HANDLING               */
/* ------------------------------------------- */

void Player::handlePlayer1Controls(float dt) {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
    if (!in_air) {
      velocity.y = -jumpForce;
      in_air = true;
    }
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
    velocity.x -= aceleration * dt;
    faced_right = -1;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
    velocity.x += aceleration * dt;
    faced_right = 1;
  }
}

void Player::handlePlayer2Controls(float dt) {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
    if (!in_air) {
      velocity.y = -jumpForce;
      in_air = true;
    }
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    velocity.x -= aceleration * dt;
    faced_right = 1;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
    velocity.x += aceleration * dt;
    faced_right = -1;
  }
}

/* ------------------------------------------- */
/*                GUN FUNCTIONS                */
/* ------------------------------------------- */

void Player::shoot() {
  if (player_num == 1) {
    if (Keyboard::isKeyPressed(sf::Keyboard::C)) {
      // Shoot after SHOOTCOOLDOWN seconds
      if (shootClock >= SHOOTCOOLDOWN) {
        Projectile *p =
            new Projectile(position.x + (size.x * faced_right), position.y,
                           Vector2f(faced_right * ROCKACEL, -8.f), this);
        p->configSprite();
        if (p) {
          addProjectile(p);
          // Register the projectile in the CollisionManager
          CollisionManager::getInstance()->addProjectile(p);
        }
        shootClock = 0.f;
      }
    }
  }
}

void Player::shootProjectiles() {
  list<Projectile *>::iterator it = projectiles_list.begin();
  while (it != projectiles_list.end()) {
    Projectile *p = *it;

    if (p && p->getActive()) {
      p->execute();
      ++it;
    } else {
      // Remove from CollisionManager before deleting
      CollisionManager::getInstance()->removeProjectile(p);

      // Delete the projectile
      delete p;
      it = projectiles_list.erase(it);
    }
  }
}

void Player::addProjectile(Projectile *p) { projectiles_list.push_back(p); }

/* ------------------------------------------- */
/*                 GETS & SETS                 */
/* ------------------------------------------- */


int Player::getHealth() const{ return health; }

int Player::getScore() const { return score; }

void Player::setJumpForce(float jpForce) { jumpForce = jpForce; }
