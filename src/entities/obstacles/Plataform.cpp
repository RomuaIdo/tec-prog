#include "../../../include/entities/obstacles/Plataform.h"
#include <SFML/Window.hpp>


Plataform::Plataform():
    Obstacle(), width(0.f), height(0.f) {
    if (!texture.loadFromFile("assets/textures/Plataform.png")) {
        std::cerr << "Failed to load Plataform.png!" << std::endl;
    }

    texture.setSmooth(true);
    sprite.setTexture(texture);
    centerOrigin();
    size.x = sprite.getLocalBounds().width;
    size.y = sprite.getLocalBounds().height;
    sprite.setScale(
        size.x / sprite.getLocalBounds().width,
        size.y / sprite.getLocalBounds().height
    );
}

Plataform::Plataform(float x, float y, bool harm):
    Obstacle(harm,x,y), width(0.f),height(0.f){
}

Plataform::~Plataform(){}

void Plataform::ObstacleAction() {
}

/* ------------------------------------------- */
/*                 GETS & SETS                 */
/* ------------------------------------------- */

void Plataform::setHeight(float h){
    height = h;
}

void Plataform::setWidth(float w){
    width = w;
}

float Plataform::getHeight() const {
    return height;
}

float Plataform::getWidth() const {
    return width;
}
