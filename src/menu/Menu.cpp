#include "../../include/menu/Menu.h"
#include "../../include/game/Game.h"


Menu::Menu() : Ente(), pGame(nullptr) {
}

Menu::Menu(Game* game) : Ente(), pGame(game) {
}

Menu::~Menu() {
  pGame = nullptr;
}

void Menu::execute() {
  
}
