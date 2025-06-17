#include "../../include/entities/Projectile.h"
#include <SFML/Window.hpp>

Projectile::Projectile():
    Entity(), active(true) , owner(nullptr) {
    
    if (!potion.loadFromFile("assets/textures/Potion.png")) {
        std::cerr << "Failed to load Potion.png!" << std::endl;
    }
    if (!bullet.loadFromFile("assets/textures/Bullet.png")) {
        std::cerr << "Failed to load Bullet.png!" << std::endl;
    }

    texture = potion;
    sprite.setTexture(texture);
    configSprite();
}

Projectile::Projectile(float x, float y, Vector2f vel, Entity* creator):
    Entity(x,y), active(true), owner(creator) {

    if (!potion.loadFromFile("assets/textures/Potion.png")) {
        std::cerr << "Failed to load Potion.png!" << std::endl;
    }
    if (!bullet.loadFromFile("assets/textures/Bullet.png")) {
        std::cerr << "Failed to load Bullet.png!" << std::endl;
    }

    setVelocity(vel);
    if(vel.x < 0){
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
    if(dynamic_cast<Enemy*>(owner)){

        if(dynamic_cast<Enemy*>(other)){

            return; // Do not collide with own team

        }else if(dynamic_cast<Player*>(other)){

            active = false; // Enemy projectile hits player
            static_cast<Player*>(other)->takeDamage(1); // Example damage value

        }else{
            active = false;
        }
    }else if(dynamic_cast<Player*>(owner)){

        if(dynamic_cast<Player*>(other)){

            return; // Do not collide with own team

        }else if(dynamic_cast<Enemy*>(other)){

            active = false; // Player projectile hits enemy
            static_cast<Enemy*>(other)->takeDamage(1); // Example damage value

        }else{
            active = false;
        }
    }else {
        cout << "Projectile owner is not a Player or Enemy!" << endl;
        active = false; // Default behavior for other types
    }
}

void Projectile::move(){
    applyGravity();
    position += velocity;
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


