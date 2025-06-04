#include "../../../include/entities/obstacles/Obstacle.h"
#include <SFML/Window.hpp>

Obstacle::Obstacle(bool harm, float x, float y):
    Entity(x,y), harmful(harm){
    if (!texture.loadFromFile("assets/textures/Obstacle.png")) {
        std::cerr << "Failed to load Obstacle.png!" << std::endl;
    }    

    configSprite();
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

void Obstacle::collide(){

}

