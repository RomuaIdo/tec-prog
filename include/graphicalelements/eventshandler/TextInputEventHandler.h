// TextInputEventHandler.h
#include "EventHandler.h"
#include "../TextInputSubject.h"

class TextInputEventHandler : public EventHandler {
public:
    TextInputEventHandler(TextInputSubject& subject) : textSubject(subject) {}
    
    bool handleEvent(const sf::Event& event) override;
private:
    TextInputSubject& textSubject;
};
