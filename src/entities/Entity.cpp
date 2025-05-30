#include "../../include/entities/Entity.h"

Entity::Entity(float x, float y) :
    Ente(), position(x,y){

}

Entity::~Entity() {}

void Entity::draw() {
    pGM->draw(this);
}

Drawable& Entity::getDrawable() {
    sprite.setPosition(position);
    return sprite;
}

Vector2f Entity::getPosition() const{
    return position;
}

void Entity::setPosition(Vector2f pos){
    position = pos;
    sprite.setPosition(position);
}
