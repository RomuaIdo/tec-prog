#include "../../include/entities/Projectile.h"
#include <SFML/Window.hpp>

Texture Projectile::potion;
Texture Projectile::Rock;

Projectile::Projectile():
    Entity(), owner(nullptr), active(true){
    
}

Projectile::Projectile(float x, float y, Vector2f vel, Entity* creator):
    Entity(x,y), owner(creator),  active(true){
    
    if (!potion.loadFromFile("assets/textures/Potion.png")) {
        std::cerr << "Failed to load Potion.png!" << std::endl;
    }
    if (!Rock.loadFromFile("assets/textures/Rock.png")) {
        std::cerr << "Failed to load Rock.png!" << std::endl;
    }

    setVelocity(vel);
    if(vel.x < 0){
        sprite.setScale(-1.f,1.f);
    }else
        sprite.setScale(1.f,1.f);

    sprite.setTexture(potion);
    configSprite();
}

Projectile::~Projectile(){ 
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
            static_cast<Player*>(other)->takeDamage(POTIONDAMAGE); // Example damage value

        }else{
            active = false;
        }
    }else if(dynamic_cast<Player*>(owner)){

        if(dynamic_cast<Player*>(other)){

            return; // Do not collide with own team

        }else if(dynamic_cast<Enemy*>(other)){

            active = false; // Player projectile hits enemy
            static_cast<Enemy*>(other)->takeDamage(ROCKDAMAGE);

            // If enemy dies, increases the player score based on the difficulty of the enemy
            if(static_cast<Enemy*>(other)->getHealth() <= 0){
                static_cast<Player*>(owner)->increaseScore(SCOREMULTIPLIER * static_cast<Enemy*>(other)->getEvilness()); 
            }
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


