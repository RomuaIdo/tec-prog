#ifndef MOUSE_SUBJECT_H
#define MOUSE_SUBJECT_H
#include "MouseObserver.h"
#include <iostream>
#include <list>
using namespace sf;
using namespace std;


class MouseSubject{
    private:
        /* ---- VARIABLES ---- */
        list<MouseObserver*> observers;

    public:
        MouseSubject();
        ~MouseSubject();

        /* ----- OBSERVER ---- */
        void addObserver(MouseObserver* observer);
        void removeObserver(MouseObserver* observer);
        void notifyObservers(const Event::MouseMoveEvent& event);
        void notifyObservers(const Event::MouseButtonEvent& event);
};


#endif
