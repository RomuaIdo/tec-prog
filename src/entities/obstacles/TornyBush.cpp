#include "../../../include/entities/obstacles/TornyBush.h"
#include <SFML/Window.hpp>


TornyBush::TornyBush(float x, float y, bool harm):
    Obstacle(harm,x,y){
}

TornyBush::~TornyBush(){}

/* ------------------------------------------- */
/*                OWN FUNCTIONS                */
/* ------------------------------------------- */

void TornyBush::execute(){
    draw();
}

void TornyBush::obstacleAction(Entity* e){
    if(Character* p = dynamic_cast<Character*>(e)){
        dealDamage(p);
    }
}

void TornyBush::collide(Entity* e){
    obstacleAction(e);
}

/* ------------------------------------------- */
/*                 GETS & SETS                 */
/* ------------------------------------------- */

void TornyBush::dealDamage(Character* character){
    if (character) {
        character->takeDamage(spikes);
    }
}
