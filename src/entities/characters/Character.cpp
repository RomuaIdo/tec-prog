#include "../../../include/entities/characters/Character.h"
#include <SFML/Window.hpp>

Vector2f Character::gravity(0.f, 30.f);

Character::Character(float x, float y, const float movSpeed, int life, float coef, int s):
    Entity(x, y), health(life), friction_coef(coef), friction(0.f,0.f), strength(s), aceleration(movSpeed), speed(0.f, 0.f){
    faced_right = 1;
}

Character::~Character(){

}

/* ------------------------------------------- */
/*                OWN FUNCTIONS                */
/* ------------------------------------------- */

void Character::moveCharacter(){
    speed += gravity * pGM->getdt();
    position += speed;
    sprite.setPosition(position);
}

/* ------------------------------------------- */
/*                 GETS & SETS                 */
/* ------------------------------------------- */

Vector2f Character::getSpeed() const{
    return speed;
}

void Character::setSpeed(Vector2f spd){
    speed = spd;
}

int Character::getStrength() const{
    return strength;
}

bool Character::getInAir() const{
    return in_air;
}

void Character::changeInAir(){
    in_air = !in_air;
}