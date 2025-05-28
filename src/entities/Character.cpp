#include "../../include/entities/Enemy.h"
#include "../../include/managers/GraphicsManager.h"
#include <SFML/Window.hpp>

Vector2f Character::gravity(0.f, 30.f);

Character::Character(const float size, float x, float y, const float movSpeed, int life, float coef, int s):
    Entity(size, x, y), health(life), friction_coef(coef), friction(), strength(s), movimentSpeed(movSpeed), velocity(0.f, 0.f){

}

void Character::collide(){
    sf::Vector2f pos = shape.getPosition();
    sf::Vector2f size = shape.getSize();


    float window_width = 800.0f;  // example
    float window_height = 600.0f; // example

    // Left wall
    if (pos.x < 0){
        shape.setPosition(0, pos.y);
        velocity.x = 0;
    }    
    // Right wall
    if (pos.x + size.x > window_width){
        shape.setPosition(window_width - size.x, pos.y);
        velocity.x = 0;
    }   
    // Top wall
    if (pos.y < 0){

        shape.setPosition(pos.x, 0);
        velocity.y = 0;
        // Bottom wall
    }if (pos.y + size.y > window_height){
        shape.setPosition(pos.x, window_height - size.y);
        velocity.y = 0;
    }

}
