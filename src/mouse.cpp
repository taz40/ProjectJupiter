#include "mouse.h"
#include "Events.h"

MouseDriver::MouseDriver(InterruptManager* manager)
: InterruptHandler(manager, 0x2C),
dataport(0x60),
commandport(0x64){
    offset = 2;
    buttons = 0;
    
    commandport.Write(0xFF);
                            
    commandport.Write(0xA8);
    commandport.Write(0x20);
    uint8_t status = (dataport.Read() | 2);
    commandport.Write(0x60);
    dataport.Write(status);
    
    commandport.Write(0xD4);
    dataport.Write(0xF4);
    dataport.Read();
}

MouseDriver::~MouseDriver(){
    
}

uint32_t MouseDriver::HandleInterrupt(uint32_t esp){
    
    uint8_t status = commandport.Read();
    if(!(status & 0x20)){
        return esp;
    }
    
    buffer[offset] = dataport.Read();
    offset = (offset + 1) % 3;
    
    if(offset == 0){                  
        if(buffer[1] == 0 && buffer[2] == 0)
            return esp;
        
        MouseEvent* event = new MouseEvent();
        event->Movement_X = buffer[1];
        event->Movement_Y = -buffer[2];
        Event* e = new Event();
        e->type = EventType::EVENT_MOUSE;
        e->data = (uint8_t*)event;
        EventManager::activeEventManager->AddEvent(*e);
    }
    return esp;
}
