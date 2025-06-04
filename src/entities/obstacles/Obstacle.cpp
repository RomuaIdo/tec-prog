#include "../../../include/entities/obstacles/Obstacle.h"
#include <SFML/Window.hpp>

Obstacle::Obstacle(bool harm, float x, float y):
    Entity(x,y), harmful(harm){
    if (!texture.loadFromFile("assets/textures/Obstacle.png")) {
        std::cerr << "Failed to load Obstacle.png!" << std::endl;
    }    

    texture.setSmooth(true);
    sprite.setTexture(texture);

    
    sprite.setOrigin(Vector2f(sprite.getPosition().x + sprite.getGlobalBounds().width  / static_cast<float> (2), 
    sprite.getPosition().y + sprite.getGlobalBounds().height / static_cast<float> (2)));
    size = Vector2f(sprite.getGlobalBounds().width / 2.f, sprite.getGlobalBounds().height / 2.f);

    sprite.setScale(1.f, 1.f);
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

