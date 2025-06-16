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
    void execute() override;
private:
    Font font;
    Text phaseText;
    int currentPhase;
};

#endif
