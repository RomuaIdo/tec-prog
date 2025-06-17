#include "../../../include/entities/obstacles/Obstacle.h"
#include <SFML/Window.hpp>

Obstacle::Obstacle():
    Entity(), harmful(false) {
}

Obstacle::Obstacle(float x, float y, bool harm):
    Entity(x,y), harmful(harm){
    /**/
}

Obstacle::~Obstacle(){

}

/* ------------------------------------------- */
/*                OWN FUNCTIONS                */
/* ------------------------------------------- */



