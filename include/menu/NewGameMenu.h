#ifndef NEWGAMEMENU_H
#define NEWGAMEMENU_H

#include "Menu.h"
#include <SFML/Graphics.hpp>

class NewGameMenu : public Menu {
public:
    NewGameMenu(Game* game);
    virtual ~NewGameMenu();

    void createButtons();
    void updatePhaseDisplay();
    void updatePlayersDisplay();
    void execute() override;
private:
    Font font;
    Text phaseText;
    Text playersText;
    int currentPhase;
    int players;
};

#endif
