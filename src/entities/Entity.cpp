#include "../../include/entities/Entity.h"

Entity::Entity(const float size, float x, float y) :
    Ente(), grid_size(size){
    shape.setPosition(x,y);
    shape.setSize(sf::Vector2f(grid_size, grid_size));
}

Entity::~Entity() {}

void Entity::draw() {
    pGM->draw(this); // Usa o Gerenciador Gráfico
}

Drawable& Entity::getDrawable() {
    
    return sprite;
}

sf::RectangleShape Entity::getShape() { 
    return shape; 
}

