#ifndef MAINMENU_H
#define MAINMENU_H

#include "Menu.h"
#include <SFML/Graphics.hpp>

class MainMenu : public Menu {
public:
    MainMenu(Game* game);
    virtual ~MainMenu();
    void createButtons();
    void setGameTitle(const string& title);
    void execute() override;
private:
    Text GameTitle;
    Font font;
};

#endif
