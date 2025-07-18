#include "../../include/menu/Menu.h"
#include "../../include/game/Game.h"

Menu::Menu() : Ente(), pGame(nullptr){
}

Menu::Menu(Game *game) : Ente(), pGame(game){
}

Menu::~Menu(){
    pGame = nullptr;
    map<string, Button *>::iterator it;
    for (it = buttons.begin(); it != buttons.end(); ++it)
    {
        delete it->second;
    }
    buttons.clear();
}

/* ------------------------------------------- */
/*                OWN FUNCTIONS                */
/* ------------------------------------------- */

void Menu::execute(){
    draw();
    map<string, Button *>::iterator it;
    for (it = buttons.begin(); it != buttons.end(); ++it)
        it->second->execute();
}

void Menu::draw(){
    pGM->draw(this);
}

Drawable &Menu::getDrawable(){
    return sprite;
}

void Menu::activate(){
    activateButtons();
}

void Menu::deactivate(){
    deactivateButtons();
}

/* ------------------------------------------- */
/*               BUTTON FUNCTIONS              */
/* ------------------------------------------- */

void Menu::activateButtons(){
    map<string, Button *>::iterator it;
    for (it = buttons.begin(); it != buttons.end(); ++it)
        it->second->activate();
}

void Menu::deactivateButtons(){
    map<string, Button *>::iterator it;
    for (it = buttons.begin(); it != buttons.end(); ++it)
        it->second->deactivate();
}

void Menu::addButton(string name, Button *button){
    if (buttons.find(name) == buttons.end())
        buttons[name] = button;
    else
        cerr << "Button with name '" << name << "' already exists!" << endl;
}

/* ------------------------------------------- */
/*                 GETS & SETS                 */
/* ------------------------------------------- */

void Menu::setBackground(const string filePath){
    background = pGM->loadTexture(filePath);
    sprite.setTexture(background);
    sprite.setPosition(0, -250);
}

map<string, Button *> &Menu::getButtons(){
    return buttons;
}
