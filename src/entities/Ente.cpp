#include "../../include/entities/Ente.h"

GraphicsManager* Ente::pGM = GraphicsManager::getInstance();
Ente::Ente():
    sprite(), texture(){

}

Ente::~Ente() {
    pGM = nullptr;
}
