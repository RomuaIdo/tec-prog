#include "../../../include/entities/obstacles/Honey.h"
#include <SFML/Window.hpp>


Honey::Honey(float x, float y, bool harm):
    Obstacle(x,y,harm), viscosity(0.6f){
    if (!texture.loadFromFile("assets/textures/Honey.png")) {
        std::cerr << "Failed to load Honey.png!" << std::endl;
    }
    sprite.setTexture(texture);
    configSprite();
}

Honey::~Honey(){}

/* ------------------------------------------- */
/*                OWN FUNCTIONS                */
/* ------------------------------------------- */

void Honey::execute(){
    draw();
}

void Honey::obstacleAction(Entity* e){
    if (e) {
        Character* character = dynamic_cast<Character*>(e);
        if (character) {
            Vector2f speed = character->getSpeed();
            speed.x *= viscosity; // Slow down the character's speed
            speed.y *= (viscosity); // Slow down the character's jump
            character->setSpeed(speed);
        }
    }
}

void Honey::collide(Entity* e){
    obstacleAction(e);
}

/* ------------------------------------------- */
/*                 GETS & SETS                 */
/* ------------------------------------------- */

void Honey::setViscosity(float v){
    viscosity = v;
}

float Honey::getViscosity() const {
    return viscosity;
}


