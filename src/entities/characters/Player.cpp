#include "../../../include/entities/characters/Player.h"
#include "../../../include/managers/CollisionManager.h"
#include <SFML/Window.hpp>

Player::Player(float x, float y, const float acel, int life, float coef, int s, int p_num, const float v_max): 
    Character(x, y, acel, life, coef, s), player_num(p_num), score(0), vel_max(v_max), projectiles_list(), shoot_delay(0.f){
    projectiles_list.clear();
    
    if(p_num == 1){
        if (!texture.loadFromFile("assets/textures/Emilia.png")) {
            std::cerr << "Failed to load Emilia.png!" << std::endl;
        }    
    }
    else {
        if (!texture.loadFromFile("assets/textures/Player2Sprite.png")) {
            std::cerr << "Failed to load Player2Sprite.png!" << std::endl;
        }  
    }
    sprite.setTexture(texture);
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
    if (velocity.x > max_vel)
        velocity.x = max_vel;
    if (velocity.x < -max_vel)
        velocity.x = -max_vel;

    applyFriction(dt);
    moveCharacter();
}

void Player::handlePlayer1Controls(float dt, float jumpForce) {
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

void Player::handlePlayer2Controls(float dt, float jumpForce) {
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

void Player::collide(Entity* e){
    Vector2f ePos = e->getPosition();
    Vector2f eSize = e->getSize();

    float dx = (position.x - ePos.x);
    float dy = (position.y - ePos.y);
    // Vector2f variation = Vector2f(dx, dy);

    /* If dx > 0 -> a in b's right  */
    
    /* If dy > 0 -> a is below b    */

    /* The intersection between a and b ,
    *   if they collide, the vector will be
    *   negative in x and y                */

    Vector2f intersection = Vector2f( abs(dx) - (size.x + eSize.x), 
                                      abs(dy) - (size.y + eSize.y) );

    if (intersection.x < 0.0f && intersection.y < 0.0f) {

        /* If intersection in x is less then intersection in y
        /*  means that they are side by side                 */

        if (std::abs(intersection.x) < std::abs(intersection.y)) {
            
            /* To push the character the amount he is inside */                       
            float push = abs(intersection.x / 2.f);

            if (dx > 0) {
                position.x += push;
                setVelocity({0.f + push, getVelocity().y});
            }
            else{
                position.x -= push;
                setVelocity({0.f - push, getVelocity().y});
            } 


        /* If intersection in y is less then intersection in x
        /*  means that character collided in y with obstacle */

        } else {

            /* To push the character the amount he is inside */ 
            float push = abs(intersection.y / 2.f);

            /* c is below o */
            if (dy > 0) {

                position.y += push;

            /* c is on top of o */
            } else {

                /* c can jump */
                setInAir(false);
                position.y -= push;

                setVelocity({ getVelocity().x, 0.f });
            }
        }
        setPosition(position);
    }
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
                Projectile *p = new Projectile(position.x + (size.x * faced_right), position.y, Vector2f(faced_right * 10.f, -10.f));

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
