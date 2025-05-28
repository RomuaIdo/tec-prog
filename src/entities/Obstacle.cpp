#include "../../include/entities/Obstacle.h"
#include "../../include/managers/GraphicsManager.h"
#include <SFML/Window.hpp>

Obstacle::Obstacle(bool harm, float x, float y):
    Entity(x,y), harmful(harm){
    if (!texture.loadFromFile("sprites/Obstacle.png")) {
        std::cerr << "Failed to load Obstacle.png!" << std::endl;
    }    

    texture.setSmooth(true);
    sprite.setTexture(texture);
    size.x = sprite.getLocalBounds().width;
    size.y = sprite.getLocalBounds().height;
    sprite.setScale(    
    size.x / sprite.getLocalBounds().width,
    size.y / sprite.getLocalBounds().height
    );
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