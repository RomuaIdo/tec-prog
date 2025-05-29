#include "../../include/entities/Ente.h"
#include "../../include/managers/GraphicsManager.h"

Ente::Ente():
    sprite(), texture(){

}

Ente::~Ente() {
    pGM = nullptr;
}
