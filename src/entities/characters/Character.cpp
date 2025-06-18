#include "../../../include/entities/characters/Character.h"
#include <SFML/Window.hpp>


Character::Character(float x, float y, const float acel, int life, int s):
    Entity(x, y), aceleration(acel), health(life), strength(s), 
    takeDamageClock(0.f), friction(0.f,0.f), faced_right(1){
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
    setPosition(position);
}

void Character::takeDamage(int damage){
    if(health - damage < 0){
        health = 0;
        cout << "Character is dead!" << endl;
    }else{
        health -= damage;
        cout << "Lost Health:" << health << endl;
    }
}

void Character::applyFriction(float dt) {
    if (velocity.x > 0) {
        friction.x = -FRICTION;
        if (velocity.x + friction.x * dt < 0) {
            velocity.x = 0;
            friction.x = 0; // Stop friction when velocity is zero
        }
    } else if (velocity.x < 0) {
        friction.x = FRICTION;
        if (velocity.x + friction.x * dt > 0) {
            velocity.x = 0;
            friction.x = 0; // Stop friction when velocity is zero
        }
    } else {
        friction.x = 0;
    }
    velocity += friction * dt;
   
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
