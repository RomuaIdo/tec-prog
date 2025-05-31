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
  draw();
  map<string, Button*>::iterator it;
  for (it = buttons.begin(); it != buttons.end(); ++it) {
    it->second->execute();
  }
}

void Menu::addButton(string name, Button* button) {
  if (buttons.find(name) == buttons.end()) {
    buttons[name] = button;
  } else {
    cerr << "Button with name '" << name << "' already exists!" << endl;
  }
}

map<string, Button*>& Menu::getButtons() {
  return buttons;
}

void Menu::activateButtons() {
  map<string, Button*>::iterator it;
  for (it = buttons.begin(); it != buttons.end(); ++it) {
    it->second->activate();
  }
}

void Menu::deactivateButtons() {
  map<string, Button*>::iterator it;
  for (it = buttons.begin(); it != buttons.end(); ++it) {
    it->second->deactivate();
  }
}

void Menu::draw() {
  pGM->draw(this);
}

void Menu::setBackground(const string filePath) {
  background.loadFromFile(filePath);
  sprite.setTexture(background);
}

Drawable& Menu::getDrawable() {
  return sprite;
}
