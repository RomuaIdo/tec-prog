#include "../../include/entities/Plataform.h"
#include "../../include/managers/GraphicsManager.h"
#include <SFML/Window.hpp>

Plataform::Plataform(const float size, float x, float y, bool harm):
    Obstacle(harm,size,x,y), width(0.f), height(0.f){

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
