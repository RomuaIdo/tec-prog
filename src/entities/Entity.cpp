#include "../../include/entities/Entity.h"

Entity::Entity(float x, float y) :
    Ente(), position(x,y){
    // shape.setPosition(x,y);
    // shape.setSize(sf::Vector2f(grid_size, grid_size));
}

Entity::~Entity() {}

void Entity::draw() {
    pGM->draw(this); // Usa o Gerenciador Gráfico
}

Drawable& Entity::getDrawable() {
    // sprite.setPosition(shape.getPosition());
    sprite.setPosition(position);
    return sprite;
}

// sf::RectangleShape Entity::getShape() { 
//     return shape; 
// }

Vector2f Entity::getPosition(){ return position; }
