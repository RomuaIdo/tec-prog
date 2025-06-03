#include "../../../include/entities/characters/Character.h"
#include <SFML/Window.hpp>

Vector2f Character::gravity(0.f, 30.f);

Character::Character(float x, float y, const float movSpeed, int life, float coef, int s):
    Entity(x, y), health(life), friction_coef(coef), friction(0.f,0.f), strength(s), aceleration(movSpeed), speed(0.f, 0.f), onGround(false) {
    
}

Character::~Character(){

}

void Character::moveCharacter() {
    if (!onGround) {
        speed.y += gravity.y * pGM->getdt();
    }
    
    position += speed;
    sprite.setPosition(position);
    
    onGround = false; // Resetar para o próximo frame
}


Vector2f Character::getVelocity() const{
    return speed;
}

void Character::setVelocity(Vector2f vel){
    speed = vel;
}

void Character::setOnGround(bool onground){
    onGround = onground;
}

bool Character::isOnGround() const{
    return onGround;
}
