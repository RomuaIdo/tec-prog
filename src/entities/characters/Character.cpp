#include "../../../include/entities/characters/Character.h"
#include <SFML/Window.hpp>

Vector2f Character::gravity(0.f, 30.f);

Character::Character(float x, float y, const float movVelocity, int life, float coef, int s):
    Entity(x, y), health(life), strength(s), aceleration(movVelocity), velocity(0.f, 0.f), clock(0.f), faced_right(1), friction(0.f,0.f), friction_coef(coef){
}

Character::~Character(){

}

/* ------------------------------------------- */
/*                OWN FUNCTIONS                */
/* ------------------------------------------- */

void Character::moveCharacter(){
    velocity += gravity * pGM->getdt();
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

Vector2f Character::getVelocity() const{
    return velocity;
}

void Character::setVelocity(Vector2f spd){
    velocity = spd;
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
