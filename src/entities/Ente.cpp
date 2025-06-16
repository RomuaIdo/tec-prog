#include "../../include/entities/Ente.h"

Ente::Ente() : sprite(), texture() {}

/* ------------------------------------------- */
/*                OWN FUNCTIONS                */
/* ------------------------------------------- */

void Ente::centerOrigin() {
  FloatRect bounds = sprite.getLocalBounds();
  sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void Ente::draw() {
    pGM->draw(this);
}

Drawable& Ente::getDrawable() {
    return sprite;
}

void Ente::configSprite(){
    sprite.setOrigin(sprite.getGlobalBounds().width / 2.f, sprite.getGlobalBounds().height / 2.f);
    size = Vector2f(sprite.getGlobalBounds().width / 2.f, sprite.getGlobalBounds().height / 2.f);
}

/* ------------------------------------------- */
/*                 GETS & SETS                 */
/* ------------------------------------------- */

void Ente::setTexture(Texture t){
    texture = t;
    sprite.setTexture(t);
    configSprite();
}

Vector2f Ente::getPosition() const {
    return sprite.getPosition();
}

Vector2f Ente::getSize() const{
    return size;
}

void Ente::setPosition(Vector2f pos){
    sprite.setPosition(pos);
}

void Ente::setGraphicsManager(GraphicsManager* pGM) {
    Ente::pGM = pGM;
}

GraphicsManager* Ente::pGM = nullptr;
