#include "../../../include/entities/characters/Character.h"
#include <SFML/Window.hpp>

Vector2f Character::gravity(0.f, 30.f);

Character::Character(float x, float y, const float movSpeed, int life, float coef, int s):
    Entity(x, y), health(life), friction_coef(coef), friction(0.f,0.f), strength(s), movimentSpeed(movSpeed), velocity(0.f, 0.f){
    
}

Character::~Character(){

}

void Character::moveCharacter(){
    const float vel_max = 50.f;

    // See if velocity ultrapassed vel_max
    if (velocity.x > vel_max){
        if(velocity.y > vel_max)
            velocity.y = vel_max;
        velocity.x = vel_max;
    }else if( velocity.y > vel_max){
        if(velocity.x > vel_max)
            velocity.x = vel_max;
        velocity.y = vel_max;
    }
    if (velocity.x < -vel_max){
        if(velocity.y < -vel_max)
            velocity.y = -vel_max;
        velocity.x = -vel_max;
    }else if( velocity.y < -vel_max){
        if(velocity.x < -vel_max)
            velocity.x = -vel_max;
        velocity.y = -vel_max;
    }

    // Apply friction
    if(velocity.x > 0){
        friction.x = -gravity.y * friction_coef;
        if(velocity.x + friction.x * pGM->getdt() < 0) {
           velocity.x = 0;
            friction.x = 0;
        }
    }
    else if(velocity.x <0){
        friction.x = gravity.y * friction_coef;
        if(velocity.x + friction.x * pGM->getdt() > 0) {
            velocity.x = 0;
            friction.x = 0;
        }
    }
    else
        friction.x = 0;
    
    velocity += gravity * pGM->getdt();
    velocity += friction * pGM->getdt();
    position += velocity;
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
