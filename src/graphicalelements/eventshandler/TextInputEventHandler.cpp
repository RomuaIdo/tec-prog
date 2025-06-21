#include "../../../include/graphicalelements/eventshandler/TextInputEventHandler.h"

bool TextInputEventHandler::handleEvent(const sf::Event &event) {
  if (event.type == sf::Event::TextEntered) {
    textSubject.notifyObservers(event.text);
    return true;
  }
  return (nextHandler) ? nextHandler->handleEvent(event) : false;
}
