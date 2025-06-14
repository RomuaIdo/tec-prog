#include "../../../include/entities/obstacles/ThornyBush.h"
#include <SFML/Window.hpp>


ThornyBush::ThornyBush(float x, float y, bool harm):
    Obstacle(harm,x,y){
}

ThornyBush::~ThornyBush(){}

/* ------------------------------------------- */
/*                OWN FUNCTIONS                */
/* ------------------------------------------- */

void ThornyBush::execute(){
    draw();
}

void ThornyBush::obstacleAction(Entity* e){
    if(Character* p = dynamic_cast<Character*>(e)){
        dealDamage(p);
    }
}

void ThornyBush::collide(Entity* e){
    obstacleAction(e);
}

/* ------------------------------------------- */
/*                 GETS & SETS                 */
/* ------------------------------------------- */

void ThornyBush::dealDamage(Character* character){
    if (character) {
        character->takeDamage(spikes);
    }
}
