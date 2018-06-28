#include "keyboard.h"

void terminal_putchar(char c);
void printDebugSerial(const char* string);
void printHexSerial(uint32_t hex);

bool shift = false;

char keys[] = {
    ' ',
    ' ',
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
    ' ',
    ' ',
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
    ' ',
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
    ' ',
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
    ' ',
    '*',
    ' ',
    ' ',
    ' ',
    ' ',
    ' ',
    ' ',
    ' ',
    ' ',
    ' ',
    ' ',
    ' ',
    ' ',
    ' ',
    ' ',
    ' ',
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
    '0'

};

char keysShift[] = {
    ' ',
    ' ',
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
    ' ',
    ' ',
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
    ' ',
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
    '\"',
    '~',
    ' ',
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
    ' ',
    '*',
    ' ',
    ' ',
    ' ',
    ' ',
    ' ',
    ' ',
    ' ',
    ' ',
    ' ',
    ' ',
    ' ',
    ' ',
    ' ',
    ' ',
    ' ',
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
    '0'
};

KeyboardDriver::KeyboardDriver(InterruptManager* manager)
: InterruptHandler(manager, 0x21),
dataport(0x60),
commandport(0x64){
    while(commandport.Read() & 0x1)
        dataport.Read();
    commandport.Write(0xAE);
    commandport.Write(0x20);
    uint8_t status = (dataport.Read() | 1) & ~0x10;
    commandport.Write(0x60);
    dataport.Write(status);
    dataport.Write(0xF4);
}

KeyboardDriver::~KeyboardDriver(){
}

uint32_t KeyboardDriver::HandleInterrupt(uint32_t esp){
    uint8_t key = dataport.Read();
    if(key < 0x80){
        switch(key){
            
            case 0x2A: shift = true; break;
            case 0x36: shift = true; break;
            
            default:
            
            if((sizeof(keys)/sizeof(*keys)) > key){
                if(!shift){
                    terminal_putchar(keys[key]);
                }else{
                    terminal_putchar(keysShift[key]);
                }
            }else{
                printDebugSerial("Keyboard 0x");
                printHexSerial(key);
                printDebugSerial("\n");
            }
        }
    }else if(key == 0xAA || key == 0xB6){
        shift = false;
    }
    
    return esp;
}
