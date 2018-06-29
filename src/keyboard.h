#ifndef __KEYBOARD_H
#define __KEYBOARD_H

#include "types.h"
#include "interrupts.h"
#include "port.h"

enum KeyCode{
    VK_NONE,
    VK_ESCAPE,
    VK_1,
    VK_2,
    VK_3,
    VK_4,
    VK_5,
    VK_6,
    VK_7,
    VK_8,
    VK_9,
    VK_0,
    VK_MINUS,
    VK_EQUALS,
    VK_BACKSPACE,
    VK_TAB,
    VK_Q,
    VK_W,
    VK_E,
    VK_R,
    VK_T,
    VK_Y,
    VK_U,
    VK_I,
    VK_O,
    VK_P,
    VK_LBRACKET,
    VK_RBRACKET,
    VK_ENTER,
    VK_LCTRL,
    VK_A,
    VK_S,
    VK_D,
    VK_F,
    VK_G,
    VK_H,
    VK_J,
    VK_K,
    VK_L,
    VK_SEMICOLON,
    VK_QUOTE,
    VK_BACKTICK,
    VK_LSHIFT,
    VK_BACKSLASH,
    VK_Z,
    VK_X,
    VK_C,
    VK_V,
    VK_B,
    VK_N,
    VK_M,
    VK_COMMA,
    VK_PERIOD,
    VK_SLASH,
    VK_RSHIFT,
    VK_NUMASTRISK,
    VK_LALT,
    VK_SPACE,
    VK_CAPSLOCK,
    VK_F1,
    VK_F2,
    VK_F3,
    VK_F4,
    VK_F5,
    VK_F6,
    VK_F7,
    VK_F8,
    VK_F9,
    VK_F10,
    VK_NUMLOCK,
    VK_SCROLLLOCK,
    VK_NUM7,
    VK_NUM8,
    VK_NUM9,
    VK_NUMMINUS,
    VK_NUM4,
    VK_NUM5,
    VK_NUM6,
    VK_NUMPLUS,
    VK_NUM1,
    VK_NUM2,
    VK_NUM3,
    VK_NUM0,
    VK_NUMPERIOD,
    VK_F11,
    VK_F12,
    VK_MMPREV,
    VK_MMNEXT,
    VK_NUMENTER,
    VK_RCTRL,
    VK_MMMUTE,
    VK_MMCALCULATOR,
    VK_MMPLAY,
    VK_MMSTOP,
    VK_MMVOLDOWN,
    VK_MMVOLUP,
    VK_MMWWWHOME,
    VK_NUMSLASH,
    VK_RALT,
    VK_HOME,
    VK_UARROW,
    VK_PAGEUP,
    VK_LARROW,
    VK_RARROW,
    VK_END,
    VK_DARROW,
    VK_PAGEDOWN,
    VK_INSERT,
    VK_DELETE,
    VK_LGUI,
    VK_RGUI,
    VK_APPS,
    VK_ACPIPOWER,
    VK_ACPISLEEP,
    VK_ACPIWAKE,
    VK_MMWWWSEARCH,
    VK_MMWWWFAVORITES,
    VK_MMWWWREFRESH,
    VK_MMWWWSTOP,
    VK_MMWWWFORWARD,
    VK_MMWWWBACK,
    VK_MMMYCOMP,
    VK_MMEMAIL,
    VK_MMSELECT,
    VK_PRINTSCRN,
    VK_PAUSE,
    
};


struct KeyEvent{
    KeyCode key;
    bool press;
    bool shift;
    bool caps;
    bool num;
    bool scroll;
};

class KeyboardDriver : public InterruptHandler{
    Port8Bit dataport;
    Port8Bit commandport;
    bool numLock;
    bool capsLock;
    bool shift;
    bool scrollLock;
    uint8_t prevMultiKey;
    bool printscrnp;
    bool printscrnr;
    bool pause;
    void setLED();
public:
    KeyboardDriver(InterruptManager* manager);
    ~KeyboardDriver();
    virtual uint32_t HandleInterrupt(uint32_t esp);
};

#endif
