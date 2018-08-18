#include "System.h"
#include "Events.h"
#include "keyboard.h"

void printlnDebugSerial(const char*);
void terminal_putchar(const char);
void terminal_writestring(const char*);

void System::Loop(){
    while(1){
        Event* e = EventManager::activeEventManager->pollEvent(EventType::EVENT_KEYBOARD);
        if(e != nullptr){
            KeyEvent* keyevent = (KeyEvent*)e->data;
            if(keyevent->press){
                terminal_putchar(keyevent->key);
                if(keyevent->keycode == VK_HOME){
                    terminal_writestring("home\n");
                }
            }
        }
    }
}

System::System(){
    
}

System::~System(){
    
}
    
void System::Start(){
    printlnDebugSerial("IDT initialized");
    printlnDebugSerial("System initialized");
    Loop();
}
