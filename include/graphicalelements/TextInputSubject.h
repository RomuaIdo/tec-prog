#ifndef TEXT_INPUT_SUBJECT_H
#define TEXT_INPUT_SUBJECT_H

#include <SFML/Window.hpp>
#include <list>
using namespace std;
using namespace sf;

class TextInputObserver;

class TextInputSubject {
private:
    list<TextInputObserver*> observers;

public:
    virtual ~TextInputSubject() = default;
    void addObserver(TextInputObserver* observer);
    void removeObserver(TextInputObserver* observer);
    void notifyObservers(const sf::Event::TextEvent& event);
};

#endif
