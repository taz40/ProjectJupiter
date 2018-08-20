#ifndef __MOUSE_H
#define __MOUSE_H

#include "types.h"
#include "interrupts.h"
#include "port.h"
#include "driver.h"

struct MouseEvent{
    int8_t Movement_X;
    int8_t Movement_Y;
    int8_t scroll;
    bool button1;
    bool button2;
    bool button3;
    bool button4;
    bool button5;
};

class MouseDriver : public InterruptHandler, public Driver{
    Port8BitSlow dataport;
    Port8BitSlow commandport;
    
    uint8_t buffer[3];
    uint8_t offset;
    uint8_t buttons;
public:
    MouseDriver(InterruptManager* manager);
    ~MouseDriver();
    virtual uint32_t HandleInterrupt(uint32_t esp);
};

#endif
