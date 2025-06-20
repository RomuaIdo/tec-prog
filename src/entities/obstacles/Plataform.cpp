#include "../../../include/entities/obstacles/Plataform.h"
#include <SFML/Window.hpp>


Plataform::Plataform() 
    : Obstacle(), isActive(false) {
}

Plataform::Plataform(float x, float y, bool harm)
    : Obstacle(x, y, harm), isActive(false){

    cloud1 = pGM->loadTexture("assets/textures/Cloud1.png");
    cloud1active = pGM->loadTexture("assets/textures/Cloud1active.png");  
    cloud2 = pGM->loadTexture("assets/textures/Cloud2.png");
    cloud2active = pGM->loadTexture("assets/textures/Cloud2active.png");  
    
    if(rand() % 2 == 0) {
        texture = cloud2;
    } else {
        texture = cloud1;
    }
    sprite.setTexture(texture);
    configSprite();
}

Plataform::~Plataform() {}

void Plataform::collide(Entity *other) {
    if (other) {
        obstacleAction(other);
    }
}

void Plataform::execute() { 
    draw(); 
}


void Plataform::obstacleAction(Entity *e) {
    isActive = false;
    float dx = (position.x - e->getPosition().x);
    float dy = (position.y - e->getPosition().y);

    Vector2f intersection = Vector2f( abs(dx) - (size.x + e->getSize().x), 
                                      abs(dy) - (size.y + e->getSize().y) );
    
    if (intersection.x < 0.0f && intersection.y < 0.0f) {
        // Collision in y
        if (std::abs(intersection.x) >= std::abs(intersection.y)){
            if (dy > 0) 
                isActive = true; // Player is on top of the platform
            else
                isActive = false;
        }else{
            isActive = false;
        }
    }

    if(isActive) {
        texture = cloud1active;
    } else {
        texture = cloud1;
    }
    sprite.setTexture(texture);
    configSprite();
    
}

/* ------------------------------------------- */
/*                 GETS & SETS                 */
/* ------------------------------------------- */

bool Plataform::getIsActive() const {
    return isActive;
}

void Plataform::setIsActive(bool active) {
    isActive = active;
}
