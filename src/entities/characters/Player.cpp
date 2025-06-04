#include "../../../include/entities/characters/Player.h"
#include <SFML/Window.hpp>

Player::Player(float x, float y, const float acel, int life, float coef, int s, int p_num, const float v_max): 
    Character(x, y, acel, life, coef, s), player_num(p_num), score(0), vel_max(v_max), projectiles_list(), shoot_delay(0.f){
    projectiles_list.clear();
    
    if(p_num == 1){
        if (!texture.loadFromFile("assets/textures/Player1Sprite.png")) {
            std::cerr << "Failed to load PlayerSprite.png!" << std::endl;
        }    
    }
    else {
        if (!texture.loadFromFile("assets/textures/Player2Sprite.png")) {
            std::cerr << "Failed to load PlayerSprite.png!" << std::endl;
        }  
    }

    configSprite();
}

Player::~Player() {
    for(list<Projectile*>::iterator it = projectiles_list.begin(); it != projectiles_list.end(); it++){
        if(*it){
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
    const float dt = pGM->getdt();
    const float jumpForce = 15.0f;
    const float max_vel = 15.0f;

    if (player_num == 1) {
        handlePlayer1Controls(dt, jumpForce);
    } else {
        handlePlayer2Controls(dt, jumpForce);
    }

    // Limits for the horizontal velocity
    if (speed.x > max_vel)
        speed.x = max_vel;
    if (speed.x < -max_vel)
        speed.x = -max_vel;

    applyFriction(dt);
    moveCharacter();
}

void Player::handlePlayer1Controls(float dt, float jumpForce) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        if (!in_air) {
            speed.y = -jumpForce;
            in_air = true;
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        speed.x -= aceleration * dt;
        faced_right = -1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        speed.x += aceleration * dt;
        faced_right = 1;
    }
}

void Player::handlePlayer2Controls(float dt, float jumpForce) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        if (!in_air) {
            speed.y = -jumpForce;
            in_air = true;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        speed.x -= aceleration * dt;
        faced_right = 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        speed.x += aceleration * dt;
        faced_right = -1;
    }
}

void Player::applyFriction(float dt) {
    if (speed.x > 0) {
        friction.x = -20.0f * friction_coef;
        if (speed.x + friction.x * dt < 0) {
            speed.x = 0;
        }
    } else if (speed.x < 0) {
        friction.x = 20.0f * friction_coef;
        if (speed.x + friction.x * dt > 0) {
        speed.x = 0;
        }
    } else {
        friction.x = 0;
    }
    speed += friction * dt;
}

void Player::collide(){
    speed = Vector2f(speed.x * -0.1f, speed.y * -0.1f);
}

void Player::execute() {
    move();
    draw();
    shoot();
    shootProjectiles();
}

/* ------------------------------------------- */
/*                GUN FUNCTIONS                */
/* ------------------------------------------- */

void Player::shoot(){
    if (player_num == 1) {
        if (Keyboard::isKeyPressed(sf::Keyboard::C)) {
            // Shoot after 0.5 seconds
            if (shoot_delay >= 0.5f) {
                Projectile *p = new Projectile(
                    position.x + (size.x * faced_right), position.y, faced_right * 10.f);

                if (p) {
                    addProjectile(p);
                    // Register the projectile in the CollisionManager
                    CollisionManager::getInstance()->addProjectile(p); 
                }
                shoot_delay = 0.f;
            }
        }
    }
    reload();
}

void Player::shootProjectiles(){
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

void Player::addProjectile(Projectile* p){
    projectiles_list.push_back(p);
}

void Player::reload(){
    shoot_delay += pGM->getdt();
}

/* ------------------------------------------- */
/*                 GETS & SETS                 */
/* ------------------------------------------- */

int Player::getHealth(){
    return health;
}

void Player::loseHealth(int damage){
    health -= damage;
}