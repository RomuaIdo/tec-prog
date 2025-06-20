#include "../../../include/entities/obstacles/Plataform.h"
#include <SFML/Window.hpp>


Plataform::Plataform() 
    : Obstacle(), isActive(false), plataformType(0), regenClock(0.0f), originalPosition(0,0) {
}

Plataform::Plataform(float x, float y, bool harm, int n)
    : Obstacle(x, y, harm), isActive(false), plataformType(n), regenClock(0.0f), originalPosition(x,y) {

    cloud1 = pGM->loadTexture("assets/textures/Cloud1.png");
    cloud1active = pGM->loadTexture("assets/textures/Cloud1active.png");  
    cloud2 = pGM->loadTexture("assets/textures/Cloud2.png");
    cloud2active = pGM->loadTexture("assets/textures/Cloud2active.png");  
    
    if(plataformType) {
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
    regenClock += pGM->getdt();
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
            if (dy > 0) {
                isActive = true; // Player is on top of the platform
                regenClock = 0.0f; // Reset regen clock
            }
            else
                isActive = false;
        }else{
            isActive = false;
        }
    }

    if(regenClock >= 1.0f && isActive) {
        isActive = false;
    }

    move();
    setState();

    sprite.setTexture(texture);
    configSprite();
    
}

void Plataform::setState(){
    if(isActive) {   
        if(plataformType) {
            texture = cloud2active;
        } else {
            texture = cloud1active;
        }
    } else {
        if(plataformType){
            texture = cloud2;
        }else{
            texture = cloud1;
        } 
    }
}

void Plataform::move(){
    if(isActive){
        if(position.y < originalPosition.y + PLATAFORMMAXPOSITION){
            position.y += PLATAFORMOVE;
        }
        if(position.y > originalPosition.y + PLATAFORMMAXPOSITION)
            position.y = originalPosition.y + PLATAFORMMAXPOSITION;
    }else{
        if(position.y > originalPosition.y){
            position.y -= PLATAFORMOVE;
        }
        if(position.y < originalPosition.y)
            position.y = originalPosition.y;
    }
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
