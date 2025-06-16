#include "../../../include/entities/characters/Character.h"
#include <SFML/Window.hpp>

Vector2f Character::gravity(0.f, 30.f);

Character::Character(float x, float y, const float movSpeed, int life, float coef, int s):
    Entity(x, y), health(life), friction_coef(coef), friction(0.f,0.f), strength(s), aceleration(movSpeed), speed(0.f, 0.f){
    faced_right = 1;
    clock = 0.f;
}

Character::~Character(){

}

/* ------------------------------------------- */
/*                OWN FUNCTIONS                */
/* ------------------------------------------- */

void Character::moveCharacter(){
    speed += gravity * pGM->getdt();
    position += speed;

    // Flip sprite based on direction
    if (faced_right == -1) {
        sprite.setScale(-1.f, 1.f); // Facing left
    } else{
        sprite.setScale(1.f, 1.f); // Facing right
    }

    sprite.setPosition(position);
}

void Character::takeDamage(int damage){
    if(health - damage < 0){
        health = 0;
        cout << "Character is dead!" << endl;
        return;
    }
    health -= damage;
    cout << "Lost Health:" << health << endl;
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

void Character::setInAir(bool inAir){
    in_air = inAir;
}