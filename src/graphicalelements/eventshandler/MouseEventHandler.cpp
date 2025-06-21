#include "../../../include/graphicalelements/eventshandler/MouseEventHandler.h"

bool MouseEventHandler::handleEvent(const sf::Event &event) {
  if (event.type == sf::Event::MouseMoved) {
    mouseSubject.notifyObservers(event.mouseMove);
    return true;
  } else if (event.type == sf::Event::MouseButtonPressed) {
    mouseSubject.notifyObservers(event.mouseButton);
    return true;
  }
  return (nextHandler) ? nextHandler->handleEvent(event) : false;
}
