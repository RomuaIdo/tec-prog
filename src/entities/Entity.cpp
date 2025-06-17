#include "../../include/entities/Entity.h"

Entity::Entity():
    Ente(), position(0.f,0.f), velocity(0.f, 0.f) {}

Entity::Entity(float x, float y) :
    Ente(), position(x,y), velocity(0.f, 0.f) {
}

Entity::~Entity() {}

Vector2f Entity::gravity(0.f, 30.f);

/* ------------------------------------------- */
/*                OWN FUNCTIONS                */
/* ------------------------------------------- */

Drawable& Entity::getDrawable() {
    sprite.setPosition(position);
    return sprite;
}

void Entity::draw() {
    pGM->draw(this);
}

void Entity::applyGravity(){
    velocity += gravity * pGM->getdt();
}

/* ------------------------------------------- */
/*                 GETS & SETS                 */
/* ------------------------------------------- */

Vector2f Entity::getVelocity() const{
    return velocity;
}

void Entity::setVelocity(Vector2f vel){
    velocity = vel;
}

Vector2f Entity::getPosition() const{
    return position;
}

void Entity::setPosition(Vector2f pos){
    position = pos;
    sprite.setPosition(position);
}