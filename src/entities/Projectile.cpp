#include "../../include/entities/Projectile.h"
#include <SFML/Window.hpp>

Projectile::Projectile(float x, float y, float vel):
    Entity(x,y), velocity(vel) {
    
    if (!texture.loadFromFile("assets/textures/spriteProjectile.png")) {
        std::cerr << "Failed to load PlayerSprite.png!" << std::endl;
    }    
    configSprite();

    active = true;
}

Projectile::~Projectile(){ 
    cout << "Projectile deleted" << endl;
}

/* ------------------------------------------- */
/*                OWN FUNCTIONS                */
/* ------------------------------------------- */

void Projectile::verifyWallCollision(){
    if(position.x - size.x < 0.f || position.x + size.x > pGM->getWindow()->getSize().x ){
        active = false;
    }
}

void Projectile::collide(Entity* e){
    
}

void Projectile::move(){
    position.x += velocity;
}

void Projectile::execute(){
    draw();
    move();
    verifyWallCollision();
}

/* ------------------------------------------- */
/*                 GETS & SETS                 */
/* ------------------------------------------- */

bool Projectile::getActive(){ 
    return active; 
}

void Projectile::desactive(){
    active = false;
}

