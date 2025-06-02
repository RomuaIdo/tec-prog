#include "../../include/entities/Ente.h"

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
void Ente::setGraphicsManager(GraphicsManager* pGM) {
    Ente::pGM = pGM;
}

GraphicsManager* Ente::pGM = nullptr;

