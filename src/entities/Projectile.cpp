#include "../../include/entities/Projectile.h"
#include <SFML/Window.hpp>

Projectile::Projectile(float x, float y, float vel):
    Entity(x,y), velocity(vel), active(true) {
    
    if (!potion.loadFromFile("assets/textures/Potion.png")) {
        std::cerr << "Failed to load Potion.png!" << std::endl;
    }
    if (!bullet.loadFromFile("assets/textures/Bullet.png")) {
        std::cerr << "Failed to load Bullet.png!" << std::endl;
    }

    if(vel < 0){
        sprite.setScale(-1.f,1.f);
    }else
        sprite.setScale(1.f,1.f);

    texture = potion;
    sprite.setTexture(texture);
    configSprite();
}

Projectile::~Projectile(){ 
    cout << "Projectile deleted" << endl;
}

/* ------------------------------------------- */
/*                OWN FUNCTIONS                */
/* ------------------------------------------- */

void Projectile::collide(Entity* other) {
    if(dynamic_cast<Character*>(other) != nullptr){
        // Handle collision with another entity
        static_cast<Character*>(other)->takeDamage(1); // Example damage value
    }
    setActive(false);
}

void Projectile::move(){
    position.x += velocity;
}

void Projectile::execute(){
    draw();
    move();
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


