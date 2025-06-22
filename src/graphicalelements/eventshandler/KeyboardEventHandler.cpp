#include "../../../include/graphicalelements/eventshandler/KeyboardEventHandler.h"

bool KeyboardEventHandler::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape || 
            event.key.code == sf::Keyboard::P) {
            
            GameState currentState = game->getGameState();
            
            if (currentState == GameState::PLAYING) {
                game->resetCamera();
                game->setGameState(GameState::PAUSED);
            } 
            else if (currentState == GameState::PAUSED) {
                game->updateCamera();
                game->setGameState(GameState::PLAYING);
            }
            return true;
        }
    }
    return (nextHandler) ? nextHandler->handleEvent(event) : false;
}
