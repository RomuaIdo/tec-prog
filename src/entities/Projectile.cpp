#include "../../include/entities/Projectile.h"
#include <SFML/Window.hpp>

Projectile::Projectile(float x, float y, float vel):
    Entity(x,y), velocity(vel) {
    
    if (!texture.loadFromFile("assets/textures/Player1Sprite.png")) {
        std::cerr << "Failed to load PlayerSprite.png!" << std::endl;
    }    

    texture.setSmooth(true);
    sprite.setTexture(texture);
    size.x = sprite.getLocalBounds().width;
    size.y = sprite.getLocalBounds().height;
    sprite.setScale(    
        size.x / sprite.getLocalBounds().width,
        size.y / sprite.getLocalBounds().height
    );
    active = true;
}


/* ------------------------------------------- */
/*                OWN FUNCTIONS                */
/* ------------------------------------------- */

void Projectile::collide(){
    if(position.x < 0.f || position.x + size.x > pGM->getWindow()->getSize().x){
        active = false;
    }
}

void Projectile::move(){
    position.x += velocity;
}

void Projectile::execute(){
    draw();
    move();
    collide();
}

/* ------------------------------------------- */
/*                 GETS & SETS                 */
/* ------------------------------------------- */

bool Projectile::getActive(){ 
    return active; 
}

void Projectile::setActive(bool Active){ 
    active = Active; 
}
