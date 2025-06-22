#include "../../include/graphicalelements/TextInputSubject.h"
#include "../../include/graphicalelements/TextInputObserver.h"

void TextInputSubject::addObserver(TextInputObserver *observer) {
  observers.push_back(observer);
  observer->setTextInputSubject(this);
}

void TextInputSubject::removeObserver(TextInputObserver *observer) {
  observers.remove(observer);
}

void TextInputSubject::notifyObservers(const Event::TextEvent &event) {
  list<TextInputObserver *>::iterator it;

  for (it = observers.begin(); it != observers.end(); ++it) {
    (*it)->onTextEntered(event);
  }
}

void TextInputObserver::setTextInputSubject(TextInputSubject *subject) {
  textInputSubject = subject;
}
