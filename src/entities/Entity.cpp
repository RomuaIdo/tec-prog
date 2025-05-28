#include "../../include/entities/Entity.h"

Entity::Entity(float x, float y) :
    Ente(), position(x,y){

}

Entity::~Entity() {}

void Entity::draw() {
    pGM->draw(this); // Usa o Gerenciador Gráfico
}

Drawable& Entity::getDrawable() {
    sprite.setPosition(position);
    return sprite;
}

Vector2f Entity::getPosition(){ return position; }
