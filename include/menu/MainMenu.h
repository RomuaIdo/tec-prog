#ifndef MAINMENU_H
#define MAINMENU_H

#include "Menu.h"
#include <SFML/Graphics.hpp>

class MainMenu : public Menu {
public:
    MainMenu(Game* game);
    virtual ~MainMenu();

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
