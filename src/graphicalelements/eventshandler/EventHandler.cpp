#include "../../../include/graphicalelements/eventshandler/EventHandler.h"

void EventHandler::setNextHandler(EventHandler *next) {
    nextHandler = next;
}
