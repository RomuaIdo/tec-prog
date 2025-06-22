#ifndef TEXT_INPUT_OBSERVER_H
#define TEXT_INPUT_OBSERVER_H

#include <SFML/Window.hpp>
using namespace sf;
class TextInputSubject;

class TextInputObserver {
private:
  TextInputSubject *textInputSubject;
public:
    TextInputObserver() = default;
    virtual ~TextInputObserver() = default;
    virtual void onTextEntered(const Event::TextEvent& event) = 0;
    void setTextInputSubject(TextInputSubject *subject);
};

#endif
