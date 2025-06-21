// MouseEventHandler.h
#include "EventHandler.h"
#include "../MouseSubject.h"

class MouseEventHandler : public EventHandler {
public:
    MouseEventHandler(MouseSubject& subject) : mouseSubject(subject) {}
    
    bool handleEvent(const sf::Event& event) override;
private:
    MouseSubject& mouseSubject;
};
