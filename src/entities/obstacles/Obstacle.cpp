#include "../../../include/entities/obstacles/Obstacle.h"
#include <SFML/Window.hpp>

Obstacle::Obstacle(bool harm, float x, float y):
    Entity(x,y), harmful(harm){
    if (!texture.loadFromFile("assets/textures/Obstacle.png")) {
        std::cerr << "Failed to load Obstacle.png!" << std::endl;
    }    

    texture.setSmooth(true);
    sprite.setTexture(texture);
    centerOrigin();
    size.x = sprite.getLocalBounds().width;
    size.y = sprite.getLocalBounds().height;
    sprite.setScale(    
        size.x / sprite.getLocalBounds().width,
        size.y / sprite.getLocalBounds().height
    );
}

Obstacle::~Obstacle(){

}

/* ------------------------------------------- */
/*                OWN FUNCTIONS                */
/* ------------------------------------------- */

void Obstacle::execute(){
    draw();
}

void Obstacle::ObstacleAction(){

}


