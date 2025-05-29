#include "../../../include/entities/characters/Character.h"
#include <SFML/Window.hpp>

Vector2f Character::gravity(0.f, 30.f);

Character::Character(float x, float y, const float movSpeed, int life, float coef, int s):
    Entity(x, y), health(life), friction_coef(coef), friction(0.f,0.f), strength(s), movimentSpeed(movSpeed), velocity(0.f, 0.f){
    
}

Character::~Character(){

}

void Character::moveCharacter(Vector2f vel){
    vel += gravity * pGM->getdt();
    position += vel;
    sprite.setPosition(position);

}

void Character::collide(){
    
    float window_width = 800.0f;  // example
    float window_height = 600.0f; // example

    // Left wall
    if (position.x < 0){
        position.x = 0;
        velocity.x = 0;
    }    
    // Right wall
    if (position.x + size.x > window_width){
        position.x = window_width - size.x;
        velocity.x = 0;
    }   
    // Top wall
    if (position.y < 0){
        position.y = 0;
        velocity.y = 0;
    }
    // Bottom wall
    if (position.y + size.y > window_height){
        position.y = window_height - size.y;
        velocity.y = 0;
    }

}

Vector2f Character::getVelocity() const{
    return velocity;
}