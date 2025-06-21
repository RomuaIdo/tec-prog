#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H
#include <SFML/Window/Event.hpp>


class EventHandler {
public:
  virtual ~EventHandler() = default;
  virtual bool handleEvent(const sf::Event &event) = 0;
  void setNextHandler(EventHandler *next);
protected:
  EventHandler *nextHandler = nullptr;
};
#endif
