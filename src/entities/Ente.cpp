#include "../../include/entities/Ente.h"

GraphicsManager* Ente::pGM = GraphicsManager::getInstance();
Ente::Ente():
    sprite(), texture(){
    sprite.setOrigin(Vector2f(sprite.getPosition().x + sprite.getGlobalBounds().width  / static_cast<float> (2), 
                              sprite.getPosition().y + sprite.getGlobalBounds().height / static_cast<float> (2)));
    size = Vector2f(sprite.getGlobalBounds().width / 2.f, sprite.getGlobalBounds().height / 2.f);
}

Ente::~Ente() {
    pGM = nullptr;
}

/* ------------------------------------------- */
/*                OWN FUNCTIONS                */
/* ------------------------------------------- */

void Ente::draw() {
    pGM->draw(this);
}

Drawable& Ente::getDrawable() {
    return sprite;
}

/* ------------------------------------------- */
/*                 GETS & SETS                 */
/* ------------------------------------------- */

Vector2f Ente::getPosition() const {
    return sprite.getPosition();
}

Vector2f Ente::getSize() const{
    return size;
}

void Ente::setPosition(Vector2f pos){
    sprite.setPosition(pos);
}

