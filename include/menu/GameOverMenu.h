#ifndef GAMEOVERMENU_H
#define GAMEOVERMENU_H

#include "Menu.h"
#include <SFML/Graphics.hpp>

class GameOverMenu : public Menu {
private:
    Text gameOverText;
    Font font;
public:
    GameOverMenu(Game* game);
    void execute() override;
};

#endif
