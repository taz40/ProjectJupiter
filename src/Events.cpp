#include "Events.h"
void terminal_writestring(const char* data);
void printDecimal(uint32_t dec);
void printHex(uint32_t hex);

EventManager* EventManager::activeEventManager = 0;

EventManager::EventManager(){
    activeEventManager = this;
    queue = new Event[255];
    eventNum = 0;
    QueueInUse = false;
    queueSize = 255;
}

EventManager::~EventManager(){
    if(activeEventManager == this)
        activeEventManager = 0;
}

void EventManager::AddEvent(Event event){
    while(QueueInUse);
    QueueInUse = true;
    if(eventNum == queueSize){
        for(int x = 1; x < eventNum; x++){
            queue[x-1] = queue[x]; 
        }
        eventNum--;
    }
    queue[eventNum] = event;
    eventNum++;
    QueueInUse = false;
}

Event* EventManager::pollEvent(EventType type){
    Event* result = 0;
    int index = -1;
    for(int i = 0; i < eventNum; i++){
        if(queue[i].type == type){
            result = &queue[i];
            index = i;
            break;
        }
    }
    if(index == -1)
        return nullptr;
    Event* e = result;
    while(QueueInUse);
    QueueInUse = true;
    for(int x = index+1; x < eventNum; x++){
        queue[x-1] = queue[x]; 
    }
    eventNum--;
    QueueInUse = false;
    return e;
}
