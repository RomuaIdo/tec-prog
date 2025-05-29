#include "../../include/entities/Ente.h"

GraphicsManager* Ente::pGM = GraphicsManager::getInstance();
Ente::Ente():
    sprite(), texture(){

}

Ente::~Ente() {
    pGM = nullptr;
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

