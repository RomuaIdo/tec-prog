#include "../../../include/entities/obstacles/Plataform.h"
#include <SFML/Window.hpp>


Plataform::Plataform(float x, float y, bool harm):
    Obstacle(harm,x,y), width(0.f),height(0.f){
}

Plataform::~Plataform(){}

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
