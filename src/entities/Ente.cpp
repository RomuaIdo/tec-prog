#include "../../include/entities/Ente.h"
#include "../../include/managers/GraphicsManager.h"

GraphicsManager* Ente::pGM = GraphicsManager::getInstance();
Ente::Ente():
    sprite(), texture(){

}

Ente::~Ente() {
    pGM = nullptr;
}
