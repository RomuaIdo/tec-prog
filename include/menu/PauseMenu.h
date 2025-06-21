#ifndef PAUSEMENU_H
#define PAUSEMENU_H
#include "Menu.h"

class PauseMenu : public Menu {
private:
  Text pauseText;
  Font font;
public:
    PauseMenu(Game* game);
    void execute() override;
};

#endif
