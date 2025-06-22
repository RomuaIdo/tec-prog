#ifndef MOUSE_OBSERVER_H
#define MOUSE_OBSERVER_H

#include <SFML/Window.hpp>
using namespace sf;
class MouseSubject;
class MouseObserver {
private:
  MouseSubject *mouseSubject;
public:
  virtual ~MouseObserver() = default;
  MouseObserver() = default;
  void setMouseSubject(MouseSubject *subject);
  virtual void onMouseEvent(const Event::MouseMoveEvent &event) = 0;
  virtual void onMouseEvent(const Event::MouseButtonEvent &event) = 0;
};

#endif
