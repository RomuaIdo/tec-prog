#include "../../../include/entities/characters/Character.h"
#include <SFML/Window.hpp>

Character::Character(float x, float y, const float movSpeed, int life, float coef, int s):
    Entity(x, y), health(life), strength(s), aceleration(movSpeed), 
    clock(0.f), friction(0.f,0.f), friction_coef(coef){
    faced_right = 1;
}

Character::~Character(){

}

/* ------------------------------------------- */
/*                OWN FUNCTIONS                */
/* ------------------------------------------- */

void Character::moveCharacter(){

    position += velocity;

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

int Character::getStrength() const{
    return strength;
}

bool Character::getInAir() const{
    return in_air;
}

void Character::setInAir(bool inAir){
    in_air = inAir;
}