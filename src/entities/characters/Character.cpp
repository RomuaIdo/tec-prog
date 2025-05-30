#include "../../../include/entities/characters/Character.h"
#include <SFML/Window.hpp>

Vector2f Character::gravity(0.f, 30.f);

Character::Character(float x, float y, const float movSpeed, int life, float coef, int s):
    Entity(x, y), health(life), friction_coef(coef), friction(0.f,0.f), strength(s), movimentSpeed(movSpeed), velocity(0.f, 0.f){
    
}

Character::~Character(){

}

void Character::moveCharacter(){
    velocity += gravity * pGM->getdt();
    position += velocity;
    sprite.setPosition(position);

}

Vector2f Character::getVelocity() const{
    return velocity;
}

void Character::setVelocity(Vector2f vel){
    velocity = vel;
}