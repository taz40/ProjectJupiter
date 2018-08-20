#ifndef __EVENTS_H
#define __EVENTS_H

#include "types.h"

enum EventType{
    EVENT_KEYBOARD,
    EVENT_MOUSE,
    EVENT_PACKET,
    EVENT_HARDWARE_CHANGED
};

class Event{
public:
    EventType type;
    uint8_t* data;
};

class EventManager{
private:
    Event* queue;
    uint8_t eventNum;
    bool QueueInUse;
    uint8_t queueSize;
public:
    static EventManager* activeEventManager;
    EventManager();
    ~EventManager();
    void AddEvent(Event event);
    Event* pollEvent(EventType type);
};

#endif
