#include "keyboard.h"
#include "Events.h"

void printlnDebugSerial(const char* string);
void printHex(uint32_t hex);
void terminal_writestring(const char* data);
void printBin(uint32_t bin);

char KeyboardDriver::NormKeys[126] = {
    '\0',
    '\0',
    '1',
    '2',
    '3',
    '4',
    '5',
    '6',
    '7',
    '8',
    '9',
    '0',
    '-',
    '=',
    '\0',
    '\0',
    'q',
    'w',
    'e',
    'r',
    't',
    'y',
    'u',
    'i',
    'o',
    'p',
    '[',
    ']',
    '\n',
    '\0',
    'a',
    's',
    'd',
    'f',
    'g',
    'h',
    'j',
    'k',
    'l',
    ';',
    '\'',
    '`',
    '\0',
    '\\',
    'z',
    'x',
    'c',
    'v',
    'b',
    'n',
    'm',
    ',',
    '.',
    '/',
    '\0',
    '*',
    '\0',
    ' ',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '7',
    '8',
    '9',
    '-',
    '4',
    '5',
    '6',
    '+',
    '1',
    '2',
    '3',
    '0',
    '.',
    '\0',
    '\0',
    '\0',
    '\0',
    '\n',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '/',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0'
};

char KeyboardDriver::ShiftKeys[126] = {
    '\0',
    '\0',
    '!',
    '@',
    '#',
    '$',
    '%',
    '^',
    '&',
    '*',
    '(',
    ')',
    '_',
    '+',
    '\0',
    '\0',
    'Q',
    'W',
    'E',
    'R',
    'T',
    'Y',
    'U',
    'I',
    'O',
    'P',
    '{',
    '}',
    '\n',
    '\0',
    'A',
    'S',
    'D',
    'F',
    'G',
    'H',
    'J',
    'K',
    'L',
    ':',
    '\'',
    '~',
    '\0',
    '|',
    'Z',
    'X',
    'C',
    'V',
    'B',
    'N',
    'M',
    '<',
    '>',
    '?',
    '\0',
    '*',
    '\0',
    ' ',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '7',
    '8',
    '9',
    '-',
    '4',
    '5',
    '6',
    '+',
    '1',
    '2',
    '3',
    '0',
    '.',
    '\0',
    '\0',
    '\0',
    '\0',
    '\n',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '/',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0'
};

char KeyboardDriver::CapsKeys[126] = {
    '\0',
    '\0',
    '1',
    '2',
    '3',
    '4',
    '5',
    '6',
    '7',
    '8',
    '9',
    '0',
    '-',
    '=',
    '\0',
    '\0',
    'Q',
    'W',
    'E',
    'R',
    'T',
    'Y',
    'U',
    'I',
    'O',
    'P',
    '[',
    ']',
    '\n',
    '\0',
    'A',
    'S',
    'D',
    'F',
    'G',
    'H',
    'J',
    'K',
    'L',
    ';',
    '\'',
    '`',
    '\0',
    '\\',
    'Z',
    'X',
    'C',
    'V',
    'B',
    'N',
    'M',
    ',',
    '.',
    '/',
    '\0',
    '*',
    '\0',
    ' ',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '7',
    '8',
    '9',
    '-',
    '4',
    '5',
    '6',
    '+',
    '1',
    '2',
    '3',
    '0',
    '.',
    '\0',
    '\0',
    '\0',
    '\0',
    '\n',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '/',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0'
};

char KeyboardDriver::ShiftCapsKeys[126] = {
    '\0',
    '\0',
    '!',
    '@',
    '#',
    '$',
    '%',
    '^',
    '&',
    '*',
    '(',
    ')',
    '_',
    '+',
    '\0',
    '\0',
    'q',
    'w',
    'e',
    'r',
    't',
    'y',
    'u',
    'i',
    'o',
    'p',
    '{',
    '}',
    '\n',
    '\0',
    'a',
    's',
    'd',
    'f',
    'g',
    'h',
    'j',
    'k',
    'l',
    ':',
    '\'',
    '~',
    '\0',
    '|',
    'z',
    'x',
    'c',
    'v',
    'b',
    'n',
    'm',
    '<',
    '>',
    '?',
    '\0',
    '*',
    '\0',
    ' ',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '7',
    '8',
    '9',
    '-',
    '4',
    '5',
    '6',
    '+',
    '1',
    '2',
    '3',
    '0',
    '.',
    '\0',
    '\0',
    '\0',
    '\0',
    '\n',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '/',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0',
    '\0'
};

KeyboardDriver::KeyboardDriver(InterruptManager* manager)
: InterruptHandler(manager, 0x21),
dataport(0x60),
commandport(0x64){
    while(commandport.Read() & 0x1)
        dataport.Read();
    commandport.Write(0xF4);
    numLock = true;
}

KeyboardDriver::~KeyboardDriver(){
}

uint32_t KeyboardDriver::HandleInterrupt(uint32_t esp){
    uint8_t key = dataport.Read();
    
    switch(key){
        case 0x00:
            printlnDebugSerial("Keyboard Error");
            break;
        case 0xAA:
            //printlnDebugSerial("Selft Test Passed");
            break;
        case 0xEE:
            printlnDebugSerial("Echo");
            break;
        case 0xFA:
            printlnDebugSerial("Command Acknowledged");
            break;
        case 0xFC:
            printlnDebugSerial("Self Test Failed");
            break;
        case 0xFD:
            printlnDebugSerial("Self Test Failed");
            break;
        case 0xFE:
            printlnDebugSerial("Resend Last Command");
            break;
        case 0xFF:
            printlnDebugSerial("Keyboard Error");
            break;
    }
    
    KeyCode code = KeyCode::VK_NONE;
    bool press = true;
    bool multi = false;
    switch(prevMultiKey){
        case 0xE1:
            if(key == 0x1D){
                prevMultiKey = 0x1D;
                multi = true;
            }else if(key == 0x9D && pause){
                prevMultiKey = 0x9D;
                multi = true;
            }else{
                prevMultiKey = 0;
            }
            break;
        case 0x1D:
            if(key == 0x45){
                prevMultiKey = 0;
                multi = true;
                pause = true;
            }else{
                prevMultiKey = 0;
            }
            break;
        case 0x9D:
            if(key == 0xC5){
                code = VK_PAUSE;
                prevMultiKey = 0;
                pause = false;
            }
    }
    
    if(prevMultiKey == 0xE0){
        switch(key){
            case 0x10: code = VK_MMPREV; prevMultiKey = 0; break;
            case 0x19: code = VK_MMNEXT; prevMultiKey = 0; break;
            case 0x1C: code = VK_NUMENTER; prevMultiKey = 0; break;
            case 0x1D: code = VK_RCTRL; prevMultiKey = 0; break;
            case 0x20: code = VK_MMMUTE; prevMultiKey = 0; break;
            case 0x21: code = VK_MMCALCULATOR; prevMultiKey = 0; break;
            case 0x22: code = VK_MMPLAY; prevMultiKey = 0; break;
            case 0x24: code = VK_MMSTOP; prevMultiKey = 0; break;
            case 0x2E: code = VK_MMVOLDOWN; prevMultiKey = 0; break;
            case 0x30: code = VK_MMVOLUP; prevMultiKey = 0; break;
            case 0x32: code = VK_MMWWWHOME; prevMultiKey = 0; break;
            case 0x35: code = VK_NUMSLASH; prevMultiKey = 0; break;
            case 0x38: code = VK_RALT; prevMultiKey = 0; break;
            case 0x48: code = VK_UARROW; prevMultiKey = 0; break;
            case 0x49: code = VK_PAGEUP; prevMultiKey = 0; break;
            case 0x4B: code = VK_LARROW; prevMultiKey = 0; break;
            case 0x4D: code = VK_RARROW; prevMultiKey = 0; break;
            case 0x4F: code = VK_END; prevMultiKey = 0; break;
            case 0x50: code = VK_DARROW; prevMultiKey = 0; break;
            case 0x51: code = VK_PAGEDOWN; prevMultiKey = 0; break;
            case 0x52: code = VK_INSERT; prevMultiKey = 0; break;
            case 0x53: code = VK_DELETE; prevMultiKey = 0; break;
            case 0x5B: code = VK_LGUI; prevMultiKey = 0; break;
            case 0x5C: code = VK_RGUI; prevMultiKey = 0; break;
            case 0x5D: code = VK_APPS; prevMultiKey = 0; break;
            case 0x5E: code = VK_ACPIPOWER; prevMultiKey = 0; break;
            case 0x5F: code = VK_ACPISLEEP; prevMultiKey = 0; break;
            case 0x63: code = VK_ACPIWAKE; prevMultiKey = 0; break;
            case 0x65: code = VK_MMWWWSEARCH; prevMultiKey = 0; break;
            case 0x66: code = VK_MMWWWFAVORITES; prevMultiKey = 0; break;
            case 0x67: code = VK_MMWWWREFRESH; prevMultiKey = 0; break;
            case 0x68: code = VK_MMWWWSTOP; prevMultiKey = 0; break;
            case 0x69: code = VK_MMWWWFORWARD; prevMultiKey = 0; break;
            case 0x6A: code = VK_MMWWWBACK; prevMultiKey = 0; break;
            case 0x6B: code = VK_MMMYCOMP; prevMultiKey = 0; break;
            case 0x6C: code = VK_MMEMAIL; prevMultiKey = 0; break;
            case 0x6D: code = VK_MMSELECT; prevMultiKey = 0; break;
            
            //release
            case 0x90: code = VK_MMPREV; prevMultiKey = 0; press = false; break;
            case 0x99: code = VK_MMNEXT; prevMultiKey = 0; press = false; break;
            case 0x9C: code = VK_NUMENTER; prevMultiKey = 0; press = false; break;
            case 0x9D: code = VK_RCTRL; prevMultiKey = 0; press = false; break;
            case 0xA0: code = VK_MMMUTE; prevMultiKey = 0; press = false; break;
            case 0xA1: code = VK_MMCALCULATOR; prevMultiKey = 0; press = false; break;
            case 0xA2: code = VK_MMPLAY; prevMultiKey = 0; press = false; break;
            case 0xA4: code = VK_MMSTOP; prevMultiKey = 0; press = false; break;
            case 0xAE: code = VK_MMVOLDOWN; prevMultiKey = 0; press = false; break;
            case 0xB0: code = VK_MMVOLUP; prevMultiKey = 0; press = false; break;
            case 0xB2: code = VK_MMWWWHOME; prevMultiKey = 0; press = false; break;
            case 0xB5: code = VK_NUMSLASH; prevMultiKey = 0; press = false; break;
            case 0xB8: code = VK_RALT; prevMultiKey = 0; press = false; break;
            case 0xC7: code = VK_HOME; prevMultiKey = 0; press = false; break;
            case 0xC8: code = VK_UARROW; prevMultiKey = 0; press = false; break;
            case 0xC9: code = VK_PAGEUP; prevMultiKey = 0; press = false; break;
            case 0xCB: code = VK_LARROW; prevMultiKey = 0; press = false; break;
            case 0xCD: code = VK_RARROW; prevMultiKey = 0; press = false; break;
            case 0xCF: code = VK_END; prevMultiKey = 0; press = false; break;
            case 0xD0: code = VK_DARROW; prevMultiKey = 0; press = false; break;
            case 0xD1: code = VK_PAGEDOWN; prevMultiKey = 0; press = false; break;
            case 0xD2: code = VK_INSERT; prevMultiKey = 0; press = false; break;
            case 0xD3: code = VK_DELETE; prevMultiKey = 0; press = false; break;
            case 0xDB: code = VK_LGUI; prevMultiKey = 0; press = false; break;
            case 0xDC: code = VK_RGUI; prevMultiKey = 0; press = false; break;
            case 0xDD: code = VK_APPS; prevMultiKey = 0; press = false; break;
            case 0xDE: code = VK_ACPIPOWER; prevMultiKey = 0; press = false; break;
            case 0xDF: code = VK_ACPISLEEP; prevMultiKey = 0; press = false; break;
            case 0xE3: code = VK_ACPIWAKE; prevMultiKey = 0; press = false; break;
            case 0xE5: code = VK_MMWWWSEARCH; prevMultiKey = 0; press = false; break;
            case 0xE6: code = VK_MMWWWFAVORITES; prevMultiKey = 0; press = false; break;
            case 0xE7: code = VK_MMWWWREFRESH; prevMultiKey = 0; press = false; break;
            case 0xE8: code = VK_MMWWWSTOP; prevMultiKey = 0; press = false; break;
            case 0xE9: code = VK_MMWWWFORWARD; prevMultiKey = 0; press = false; break;
            case 0xEA: code = VK_MMWWWBACK; prevMultiKey = 0; press = false; break;
            case 0xEB: code = VK_MMMYCOMP; prevMultiKey = 0; press = false; break;
            case 0xEC: code = VK_MMEMAIL; prevMultiKey = 0; press = false; break;
            case 0xED: code = VK_MMSELECT; prevMultiKey = 0; press = false; break;
            
            //multikey
            case 0x2A: printscrnp = true; multi = true; prevMultiKey = 0; break;
            case 0xB7: printscrnr = true; multi = true; prevMultiKey = 0; break;
            case 0x37: 
                if(printscrnp){
                    code = VK_PRINTSCRN;
                    printscrnp = false; 
                }
                prevMultiKey = 0; 
                break;
            case 0xAA: 
            if(printscrnr){
                code = VK_PRINTSCRN;
                printscrnp = false;
                press = false;
            }
            prevMultiKey = 0; 
            break;
            
            //failed to find multikey
            default:
                prevMultiKey = 0;
        }
    }
    
    if(code == KeyCode::VK_NONE && multi == false){
        switch(key){
            case 0x01: code = KeyCode::VK_ESCAPE; break;
            case 0x02: code = KeyCode::VK_1; break;
            case 0x03: code = KeyCode::VK_2; break;
            case 0x04: code = KeyCode::VK_3; break;
            case 0x05: code = KeyCode::VK_4; break;
            case 0x06: code = KeyCode::VK_5; break;
            case 0x07: code = KeyCode::VK_6; break;
            case 0x08: code = KeyCode::VK_7; break;
            case 0x09: code = KeyCode::VK_8; break;
            case 0x0A: code = KeyCode::VK_9; break;
            case 0x0B: code = KeyCode::VK_0; break;
            case 0x0C: code = KeyCode::VK_MINUS; break;
            case 0x0D: code = KeyCode::VK_EQUALS; break;
            case 0x0E: code = KeyCode::VK_BACKSPACE; break;
            case 0x0F: code = KeyCode::VK_TAB; break;
            case 0x10: code = KeyCode::VK_Q; break;
            case 0x11: code = KeyCode::VK_W; break;
            case 0x12: code = KeyCode::VK_E; break;
            case 0x13: code = KeyCode::VK_R; break;
            case 0x14: code = KeyCode::VK_T; break;
            case 0x15: code = KeyCode::VK_Y; break;
            case 0x16: code = KeyCode::VK_U; break;
            case 0x17: code = KeyCode::VK_I; break;
            case 0x18: code = KeyCode::VK_O; break;
            case 0x19: code = KeyCode::VK_P; break;
            case 0x1A: code = KeyCode::VK_LBRACKET; break;
            case 0x1B: code = KeyCode::VK_RBRACKET; break;
            case 0x1C: code = KeyCode::VK_ENTER; break;
            case 0x1D: code = KeyCode::VK_LCTRL; break;
            case 0x1E: code = KeyCode::VK_A; break;
            case 0x1F: code = KeyCode::VK_S; break;
            case 0x20: code = KeyCode::VK_D; break;
            case 0x21: code = KeyCode::VK_F; break;
            case 0x22: code = KeyCode::VK_G; break;
            case 0x23: code = KeyCode::VK_H; break;
            case 0x24: code = KeyCode::VK_J; break;
            case 0x25: code = KeyCode::VK_K; break;
            case 0x26: code = KeyCode::VK_L; break;
            case 0x27: code = KeyCode::VK_SEMICOLON; break;
            case 0x28: code = KeyCode::VK_QUOTE; break;
            case 0x29: code = KeyCode::VK_BACKTICK; break;
            case 0x2A: code = KeyCode::VK_LSHIFT; break;
            case 0x2B: code = KeyCode::VK_BACKSLASH; break;
            case 0x2C: code = KeyCode::VK_Z; break;
            case 0x2D: code = KeyCode::VK_X; break;
            case 0x2E: code = KeyCode::VK_C; break;
            case 0x2F: code = KeyCode::VK_V; break;
            case 0x30: code = KeyCode::VK_B; break;
            case 0x31: code = KeyCode::VK_N; break;
            case 0x32: code = KeyCode::VK_M; break;
            case 0x33: code = KeyCode::VK_COMMA; break;
            case 0x34: code = KeyCode::VK_PERIOD; break;
            case 0x35: code = KeyCode::VK_SLASH; break;
            case 0x36: code = KeyCode::VK_RSHIFT; break;
            case 0x37: code = KeyCode::VK_NUMASTRISK; break;
            case 0x38: code = KeyCode::VK_LALT; break;
            case 0x39: code = KeyCode::VK_SPACE; break;
            case 0x3A: code = KeyCode::VK_CAPSLOCK; break;
            case 0x3B: code = KeyCode::VK_F1; break;
            case 0x3C: code = KeyCode::VK_F2; break;
            case 0x3D: code = KeyCode::VK_F3; break;
            case 0x3E: code = KeyCode::VK_F4; break;
            case 0x3F: code = KeyCode::VK_F5; break;
            case 0x40: code = KeyCode::VK_F6; break;
            case 0x41: code = KeyCode::VK_F7; break;
            case 0x42: code = KeyCode::VK_F8; break;
            case 0x43: code = KeyCode::VK_F9; break;
            case 0x44: code = KeyCode::VK_F10; break;
            case 0x45: code = KeyCode::VK_NUMLOCK; break;
            case 0x46: code = KeyCode::VK_SCROLLLOCK; break;
            case 0x47: code = KeyCode::VK_NUM7; break;
            case 0x48: code = KeyCode::VK_NUM8; break;
            case 0x49: code = KeyCode::VK_NUM9; break;
            case 0x4A: code = KeyCode::VK_NUMMINUS; break;
            case 0x4B: code = KeyCode::VK_NUM4; break;
            case 0x4C: code = KeyCode::VK_NUM5; break;
            case 0x4D: code = KeyCode::VK_NUM6; break;
            case 0x4E: code = KeyCode::VK_NUMPLUS; break;
            case 0x4F: code = KeyCode::VK_NUM1; break;
            case 0x50: code = KeyCode::VK_NUM2; break;
            case 0x51: code = KeyCode::VK_NUM3; break;
            case 0x52: code = KeyCode::VK_NUM0; break;
            case 0x53: code = KeyCode::VK_NUMPERIOD; break;
            case 0x57: code = KeyCode::VK_F11; break;
            case 0x58: code = KeyCode::VK_F12; break;
            //release codes
            case 0x81: code = KeyCode::VK_ESCAPE; press = false; break;
            case 0x82: code = KeyCode::VK_1; press = false; break;
            case 0x83: code = KeyCode::VK_2; press = false; break;
            case 0x84: code = KeyCode::VK_3; press = false; break;
            case 0x85: code = KeyCode::VK_4; press = false; break;
            case 0x86: code = KeyCode::VK_5; press = false; break;
            case 0x87: code = KeyCode::VK_6; press = false; break;
            case 0x88: code = KeyCode::VK_7; press = false; break;
            case 0x89: code = KeyCode::VK_8; press = false; break;
            case 0x8A: code = KeyCode::VK_9; press = false; break;
            case 0x8B: code = KeyCode::VK_0; press = false; break;
            case 0x8C: code = KeyCode::VK_MINUS; press = false; break;
            case 0x8D: code = KeyCode::VK_EQUALS; press = false; break;
            case 0x8E: code = KeyCode::VK_BACKSPACE; press = false; break;
            case 0x8F: code = KeyCode::VK_TAB; press = false; break;
            case 0x90: code = KeyCode::VK_Q; press = false; break;
            case 0x91: code = KeyCode::VK_W; press = false; break;
            case 0x92: code = KeyCode::VK_E; press = false; break;
            case 0x93: code = KeyCode::VK_R; press = false; break;
            case 0x94: code = KeyCode::VK_T; press = false; break;
            case 0x95: code = KeyCode::VK_Y; press = false; break;
            case 0x96: code = KeyCode::VK_U; press = false; break;
            case 0x97: code = KeyCode::VK_I; press = false; break;
            case 0x98: code = KeyCode::VK_O; press = false; break;
            case 0x99: code = KeyCode::VK_P; press = false; break;
            case 0x9A: code = KeyCode::VK_LBRACKET; press = false; break;
            case 0x9B: code = KeyCode::VK_RBRACKET; press = false; break;
            case 0x9C: code = KeyCode::VK_ENTER; press = false; break;
            case 0x9D: code = KeyCode::VK_LCTRL; press = false; break;
            case 0x9E: code = KeyCode::VK_A; press = false; break;
            case 0x9F: code = KeyCode::VK_S; press = false; break;
            case 0xA0: code = KeyCode::VK_D; press = false; break;
            case 0xA1: code = KeyCode::VK_F; press = false; break;
            case 0xA2: code = KeyCode::VK_G; press = false; break;
            case 0xA3: code = KeyCode::VK_H; press = false; break;
            case 0xA4: code = KeyCode::VK_J; press = false; break;
            case 0xA5: code = KeyCode::VK_K; press = false; break;
            case 0xA6: code = KeyCode::VK_L; press = false; break;
            case 0xA7: code = KeyCode::VK_SEMICOLON; press = false; break;
            case 0xA8: code = KeyCode::VK_QUOTE; press = false; break;
            case 0xA9: code = KeyCode::VK_BACKTICK; press = false; break;
            case 0xAA: code = KeyCode::VK_LSHIFT; press = false; break;
            case 0xAB: code = KeyCode::VK_BACKSLASH; press = false; break;
            case 0xAC: code = KeyCode::VK_Z; press = false; break;
            case 0xAD: code = KeyCode::VK_X; press = false; break;
            case 0xAE: code = KeyCode::VK_C; press = false; break;
            case 0xAF: code = KeyCode::VK_V; press = false; break;
            case 0xB0: code = KeyCode::VK_B; press = false; break;
            case 0xB1: code = KeyCode::VK_N; press = false; break;
            case 0xB2: code = KeyCode::VK_M; press = false; break;
            case 0xB3: code = KeyCode::VK_COMMA; press = false; break;
            case 0xB4: code = KeyCode::VK_PERIOD; press = false; break;
            case 0xB5: code = KeyCode::VK_SLASH; press = false; break;
            case 0xB6: code = KeyCode::VK_RSHIFT; press = false; break;
            case 0xB7: code = KeyCode::VK_NUMASTRISK; press = false; break;
            case 0xB8: code = KeyCode::VK_LALT; press = false; break;
            case 0xB9: code = KeyCode::VK_SPACE; press = false; break;
            case 0xBA: code = KeyCode::VK_CAPSLOCK; press = false; break;
            case 0xBB: code = KeyCode::VK_F1; press = false; break;
            case 0xBC: code = KeyCode::VK_F2; press = false; break;
            case 0xBD: code = KeyCode::VK_F3; press = false; break;
            case 0xBE: code = KeyCode::VK_F4; press = false; break;
            case 0xBF: code = KeyCode::VK_F5; press = false; break;
            case 0xC0: code = KeyCode::VK_F6; press = false; break;
            case 0xC1: code = KeyCode::VK_F7; press = false; break;
            case 0xC2: code = KeyCode::VK_F8; press = false; break;
            case 0xC3: code = KeyCode::VK_F9; press = false; break;
            case 0xC4: code = KeyCode::VK_F10; press = false; break;
            case 0xC5: code = KeyCode::VK_NUMLOCK; press = false; break;
            case 0xC6: code = KeyCode::VK_SCROLLLOCK; press = false; break;
            case 0xC7: code = KeyCode::VK_NUM7; press = false; break;
            case 0xC8: code = KeyCode::VK_NUM8; press = false; break;
            case 0xC9: code = KeyCode::VK_NUM9; press = false; break;
            case 0xCA: code = KeyCode::VK_NUMMINUS; press = false; break;
            case 0xCB: code = KeyCode::VK_NUM4; press = false; break;
            case 0xCC: code = KeyCode::VK_NUM5; press = false; break;
            case 0xCD: code = KeyCode::VK_NUM6; press = false; break;
            case 0xCE: code = KeyCode::VK_NUMPLUS; press = false; break;
            case 0xCF: code = KeyCode::VK_NUM1; press = false; break;
            case 0xD0: code = KeyCode::VK_NUM2; press = false; break;
            case 0xD1: code = KeyCode::VK_NUM3; press = false; break;
            case 0xD2: code = KeyCode::VK_NUM0; press = false; break;
            case 0xD3: code = KeyCode::VK_NUMPERIOD; press = false; break;
            case 0xD7: code = KeyCode::VK_F11; press = false; break;
            case 0xD8: code = KeyCode::VK_F12; press = false; break;
            //multicode keys
            case 0xE0: prevMultiKey = 0xE0; break;
            case 0xE1: prevMultiKey = 0xE1; break;
        }
    }
    
    if(!numLock){
        switch(code){
            case VK_NUM7: code = VK_HOME; break;
            case VK_NUM8: code = VK_UARROW; break;
            case VK_NUM9: code = VK_PAGEUP; break;
            case VK_NUM4: code = VK_LARROW; break;
            case VK_NUM6: code = VK_RARROW; break;
            case VK_NUM1: code = VK_END; break;
            case VK_NUM2: code = VK_DARROW; break;
            case VK_NUM3: code = VK_PAGEDOWN; break;
            case VK_NUM0: code = VK_INSERT; break;
            case VK_NUMPERIOD: code = VK_DELETE; break;
            default:
                break;
        }
    }
    
    if(code != KeyCode::VK_NONE){
        if(code == VK_PAUSE){
            KeyEvent* event = new KeyEvent();
            event->keycode = code;
            event->press = press;
            event->shift = shift;
            event->caps = capsLock;
            event->num = numLock;
            event->scroll = scrollLock;
            event->key = NormKeys[code];
            Event* e = new Event();
            e->type = EventType::EVENT_KEYBOARD;
            e->data = (uint8_t*)event;
            EventManager::activeEventManager->AddEvent(*e);
            press = false;
        }else if(code == VK_LSHIFT || code == VK_RSHIFT){
            shift = press;
        }else if(code == VK_CAPSLOCK && press){
            capsLock = !capsLock;
            setLED();
        }else if(code == VK_NUMLOCK && press){
            numLock = !numLock;
            setLED();
        }else if(code == VK_SCROLLLOCK && press){
            scrollLock = !scrollLock;
            setLED();
        }
        
        char key = NormKeys[code];
        if(shift && capsLock){
            key = ShiftCapsKeys[code];
        }else if(shift){
            key = ShiftKeys[code];
        }else if (capsLock){
            key = CapsKeys[code];
        }
        
        KeyEvent* event = new KeyEvent();
        event->keycode = code;
        event->key = key;
        event->press = press;
        event->shift = shift;
        event->caps = capsLock;
        event->num = numLock;
        event->scroll = scrollLock;
        Event* e = new Event();
        e->type = EventType::EVENT_KEYBOARD;
        e->data = (uint8_t*)event;
        EventManager::activeEventManager->AddEvent(*e);
    
    }
    //printHex(key);
    //terminal_writestring("\n");
    return esp;
}

void KeyboardDriver::setLED(){
    while(commandport.Read() & 0x1)
        dataport.Read();
    uint8_t ledStatus = true & 0x1;
    ledStatus = (ledStatus < 1) + true & 0x1;
    ledStatus = (ledStatus < 1) + true & 0x1;
    commandport.Write(0xED);
    commandport.Write(0b111);
}
