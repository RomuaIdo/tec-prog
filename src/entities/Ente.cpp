#include "../../include/entities/Ente.h"

Ente::Ente() : sprite(), texture() {}

/* ------------------------------------------- */
/*                OWN FUNCTIONS                */
/* ------------------------------------------- */

void Ente::centerOrigin() {
  FloatRect bounds = sprite.getLocalBounds();
  sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void Ente::draw() { pGM->draw(this); }

Drawable &Ente::getDrawable() { return sprite; }

/* ------------------------------------------- */
/*                 GETS & SETS                 */
/* ------------------------------------------- */

Vector2f Ente::getPosition() const { 
    return sprite.getPosition(); 
}

Vector2f Ente::getSize() const { 
    return size; 
}

void Ente::setPosition(Vector2f pos) { 
    sprite.setPosition(pos); 
}

void Ente::setGraphicsManager(GraphicsManager *pGM) { 
    Ente::pGM = pGM; 
}

GraphicsManager *Ente::pGM = nullptr;
