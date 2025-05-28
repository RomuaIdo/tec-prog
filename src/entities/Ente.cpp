#include "../../include/entities/Ente.h"
#include "../../include/managers/GraphicsManager.h"

GraphicsManager* Ente::pGM = GraphicsManager::getInstance();
Ente::Ente():
    sprite(), texture(){
    size.x = sprite.getLocalBounds().width;
    size.y = sprite.getLocalBounds().height;
}

Ente::~Ente() {
    pGM = nullptr;
}
