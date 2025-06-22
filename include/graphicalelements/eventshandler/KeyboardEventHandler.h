#ifndef KEYBOARD_EVENT_HANDLER_H
#define KEYBOARD_EVENT_HANDLER_H
#include "EventHandler.h"
#include "../../game/Game.h"

class KeyboardEventHandler : public EventHandler {
private:
    Game* game;

public:
    KeyboardEventHandler(Game* game) : game(game) {}
    bool handleEvent(const sf::Event& event) override;
};

#endif
