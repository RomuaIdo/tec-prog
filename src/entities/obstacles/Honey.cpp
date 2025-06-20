#include "../../../include/entities/obstacles/Honey.h"
#include <SFML/Window.hpp>


Honey::Honey(float x, float y, bool harm):
    Obstacle(x,y,harm), viscosity(HONEYVISCOSITY){
    texture = pGM->loadTexture("assets/textures/Honey.png");

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
            character->setVelocity(character->getVelocity() * viscosity);
            // if(dynamic_cast<Player*>(character)){
            //     // static_cast<Player*>(character)->setJumpForce(PLAYERJUMPFORCE * viscosity);
            // }
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


