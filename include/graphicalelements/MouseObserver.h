#ifndef MOUSE_OBSERVER_H
#define MOUSE_OBSERVER_H

#include<SFML/Window.hpp>
using namespace sf;

class MouseObserver{
    public:
        virtual ~MouseObserver();
        MouseObserver();
        virtual void onMouseEvent(const Event::MouseMoveEvent& event) = 0;
        virtual void onMouseEvent(const Event::MouseButtonEvent& event) = 0;
};


#endif
