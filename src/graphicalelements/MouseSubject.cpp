#include "../../include/graphicalelements/MouseSubject.h"

MouseSubject::MouseSubject() {}

MouseSubject::~MouseSubject() { 
  observers.clear(); 
  cout << "MouseSubject destroyed, observers cleared." << endl;
}

void MouseSubject::addObserver(MouseObserver *observer) {
  if (observer != nullptr) {
    observers.push_back(observer);
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
