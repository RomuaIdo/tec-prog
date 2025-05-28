#include "../../include/entities/Obstacle.h"
#include "../../include/managers/GraphicsManager.h"
#include <SFML/Window.hpp>

Obstacle::Obstacle(bool harm, const float size, float x, float y):
    Entity(size,x,y), harmful(harm){
        shape.setFillColor(sf::Color::Magenta);
}

Obstacle::~Obstacle(){

}

void Obstacle::execute(){
    draw();
}

void Obstacle::ObstacleAction(){

}

void Obstacle::collide(){

}

void Obstacle::dealDamage(){

}