#include "../../include/graphicalelements/MouseSubject.h"

MouseSubject::MouseSubject() {}

MouseSubject::~MouseSubject() { 
  observers.clear(); 
}

/* ------------------------------------------- */
/*             OBSERVER FUNCTIONS              */
/* ------------------------------------------- */

void MouseSubject::addObserver(MouseObserver *observer) {
  if (observer != nullptr) {
    observers.push_back(observer);
    observer->setMouseSubject(this);
  } else {
    cerr << "Erro: Addittion of null observer in MouseSubject" << endl;
  }
}

void MouseSubject::removeObserver(MouseObserver *observer) {
  observers.remove(observer);
}

void MouseSubject::notifyObservers(const Event::MouseMoveEvent &event) {
  list<MouseObserver *>::iterator it;
  for (it = observers.begin(); it != observers.end(); it++) {
    if (*it != nullptr) {
      (*it)->onMouseEvent(event);
    }
  }
}

void MouseSubject::notifyObservers(const Event::MouseButtonEvent &event) {
  list<MouseObserver *>::iterator it;
  for (it = observers.begin(); it != observers.end(); it++) {
    if (*it != nullptr) {
      (*it)->onMouseEvent(event);
    }
  }
}

void MouseObserver::setMouseSubject(MouseSubject *subject) {
  mouseSubject = subject;
}
