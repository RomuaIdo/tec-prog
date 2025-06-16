#include "../../../include/entities/obstacles/Obstacle.h"
#include <SFML/Window.hpp>

Obstacle::Obstacle():
    Entity(), harmful(false) {
}

Obstacle::Obstacle(bool harm, float x, float y):
    Entity(x,y), harmful(harm){
    /**/
}

Obstacle::~Obstacle(){

}

/* ------------------------------------------- */
/*                OWN FUNCTIONS                */
/* ------------------------------------------- */



