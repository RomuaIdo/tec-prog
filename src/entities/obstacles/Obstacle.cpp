<<<<<<< HEAD
#include "../../../include/entities/obstacles/Obstacle.h"
#include <SFML/Window.hpp>

Obstacle::Obstacle(bool harm, float x, float y):
    Entity(x,y), harmful(harm){
    if (!texture.loadFromFile("assets/textures/Obstacle.png")) {
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
=======
#include "../../../include/entities/obstacles/Obstacle.h"
#include "../../../include/managers/GraphicsManager.h"
#include <SFML/Window.hpp>

Obstacle::Obstacle(bool harm, float x, float y):
    Entity(x,y), harmful(harm){
    if (!texture.loadFromFile("assets/textures/Obstacle.png")) {
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

>>>>>>> ad317a32e35cc3f6ff773c379935c4e283a8948c
