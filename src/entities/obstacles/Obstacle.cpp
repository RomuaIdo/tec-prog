#include "../../../include/entities/obstacles/Obstacle.h"
#include <SFML/Window.hpp>

Obstacle::Obstacle(bool harm, float x, float y):
    Entity(x,y), harmful(harm){

}

Obstacle::~Obstacle(){

}

/* ------------------------------------------- */
/*                 GETS & SETS                 */
/* ------------------------------------------- */

void Obstacle::setActive(bool active){
    is_active = active;
}

bool Obstacle::isActive() const {
    return is_active;
}

