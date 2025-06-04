#include "../../../include/entities/characters/Character.h"
#include <SFML/Window.hpp>

Vector2f Character::gravity(0.f, 30.f);


Character::Character(float x, float y, const float movSpeed, int life, float coef, int s):
    Entity(x, y), health(life), strength(s), aceleration(movSpeed), velocity(0.f, 0.f),  friction(0.f,0.f), friction_coef(coef), onGround(false) {
    

}

Character::~Character(){

}



/* ------------------------------------------- */
/*                OWN FUNCTIONS                */
/* ------------------------------------------- */

void Character::moveCharacter() {
    if (!onGround) {
        velocity.y += gravity.y * pGM->getdt();
    }
    
    position += velocity;
    sprite.setPosition(position);
    onGround = false; // Reset for the next frame
}



/* ------------------------------------------- */
/*                 GETS & SETS                 */
/* ------------------------------------------- */

Vector2f Character::getVelocity() const{
    return velocity;
}

void Character::setVelocity(Vector2f vel){
    velocity = vel;
}

void Character::setOnGround(bool onground){
    onGround = onground;
}

bool Character::isOnGround() const{
    return onGround;
}

