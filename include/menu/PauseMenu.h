#ifndef PAUSEMENU_H
#define PAUSEMENU_H
#include "Menu.h"

class PauseMenu : public Menu {
private:
  Text pauseText;
  Text saveMessage;
  Clock messageClock;
  bool saveMessageVisible;
  Font font;
public:
    PauseMenu(Game* game);
    void execute() override;
};

#endif
