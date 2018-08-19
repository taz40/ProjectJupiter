#include "types.h"
#include "gdt.h"
#include "interrupts.h"
#include "keyboard.h"
#include "memorymanagement.h"
#include "multitasking.h"
#include "Events.h"
#include "System.h"
#include "driver.h"
#include "pci.h"
 
/* Check if the compiler thinks we are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
 
/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif
 
/* Hardware text mode color constants. */
enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};

const uint16_t PIT_DATA_PORT = 0x40;
const uint16_t PIT_COMMAND_PORT = 0x43;

const uint16_t SERIAL_PORT = 0x3F8;
bool isDebugLogActivated = false;

uint64_t time = 0;
 
static inline void outb(uint16_t port, uint8_t data){
    asm volatile("outb %0, %1" : : "a" (data), "Nd"(port));
}

static inline uint8_t inb(uint16_t port){
    uint8_t value;
    asm volatile("inb %1, %0" : "=a"(value) : "Nd"(port));
    return value;
}


static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) 
{
	return fg | bg << 4;
}
 
static inline uint16_t vga_entry(unsigned char uc, uint8_t color) 
{
	return (uint16_t) uc | (uint16_t) color << 8;
}
 
size_t strlen(const char* str) 
{
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}
 
static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
 
size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;
 
void terminal_initialize(void) 
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminal_buffer = (uint16_t*) 0xB8000;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}
 
void terminal_setcolor(uint8_t color) 
{
	terminal_color = color;
}
 
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) 
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}
 
void terminal_putchar(char c) 
{
	if(c == '\0')
        return;
//     
    switch(c){
        case '\n':
            for(terminal_column; terminal_column < VGA_WIDTH; terminal_column++){
                terminal_putentryat(' ', terminal_color, terminal_column, terminal_row);
            }
            terminal_column = 0;
            if (++terminal_row == VGA_HEIGHT)
                terminal_row = 0;
            break;
        default:
            terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
            if (++terminal_column == VGA_WIDTH) {
                terminal_column = 0;
                if (++terminal_row == VGA_HEIGHT)
                    terminal_row = 0;
            }
	
	};
}
 
void terminal_write(const char* data, size_t size) 
{
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}
 
void terminal_writestring(const char* data) 
{
	terminal_write(data, strlen(data));
}

void printHex(uint32_t hex){
    uint8_t digit = hex % 16;
    hex -= digit;
    hex /= 16;
    if(hex > 0){
        printHex(hex);
    }
    const char* Digits = "0123456789ABCDEF";
    terminal_putchar(Digits[digit]);
}

void printDecimal(uint32_t dec){
    uint8_t digit = dec % 10;
    dec -= digit;
    dec /= 10;
    if(dec > 0){
        printDecimal(dec);
    }
    const char* Digits = "0123456789";
    terminal_putchar(Digits[digit]);
}

void printBin(uint32_t bin){
    uint8_t digit = bin % 2;
    bin -= digit;
    bin /= 2;
    if(bin > 0){
        printBin(bin);
    }
    const char* Digits = "01";
    terminal_putchar(Digits[digit]);
}

void initializeSerialAsOutputLog(){
    outb(SERIAL_PORT + 1, 0x00);
    outb(SERIAL_PORT + 3, 0x80);
    outb(SERIAL_PORT + 0, 0x03);
    outb(SERIAL_PORT + 1, 0x00);
    outb(SERIAL_PORT + 3, 0x03);
    outb(SERIAL_PORT + 2, 0xC7);
    outb(SERIAL_PORT + 4, 0x0B);
    isDebugLogActivated = true;
}

int serial_received(){
    return inb(SERIAL_PORT + 5) & 1;
}

char readSerial(){
    while (serial_received() == 0);
    
    return inb(SERIAL_PORT);
}

int isTransmitEmpty(){
    return inb(SERIAL_PORT + 5) & 0x20;
}

void writeSerial(char c){
    while (isTransmitEmpty() == 0);
    
    outb(SERIAL_PORT, c);
}

void printDebugSerial(const char* string){
    size_t size = strlen(string);
    if(isDebugLogActivated){
        for (size_t i = 0; i < size; i++)
            writeSerial(string[i]);
    }
}

void printlnDebugSerial(const char* string){
    if(isDebugLogActivated){
        printDebugSerial(string);
        writeSerial('\n');
    }
}

void printHexSerial(uint32_t hex){
    uint8_t digit = hex % 16;
    hex -= digit;
    hex /= 16;
    if(hex > 0){
        printHexSerial(hex);
    }
    const char* Digits = "0123456789ABCDEF";
    writeSerial(Digits[digit]);
}

void StartSystem(){
    printlnDebugSerial("initializing System");
    System* system = new System();
    system->Start();
}

char Command[512];
uint8_t commandLength;


void HandleCommand(const char* command, uint8_t commandLength){
    if(command == "ping"){
        terminal_writestring("pong!\n");
    }else{
        terminal_writestring("Unrecognized Command!\n");
    }
}


void Shell(){
    
    DriverManager* driverManager = new DriverManager();
    PeripheralComponentInterconnectController* pci = new PeripheralComponentInterconnectController();
    pci->SelectDrivers(driverManager);
    
    while(1){
    /*    Event* e = EventManager::activeEventManager->pollEvent(EventType::EVENT_KEYBOARD);
        if(e != nullptr){
            KeyEvent* keyevent = (KeyEvent*)e->data;
            if(keyevent->press){
                switch(keyevent->keycode){
                    case VK_BACKSPACE:
                        if(commandLength != 0){
                            terminal_putentryat(' ', terminal_color, --terminal_column, terminal_row);
                            commandLength--;
                            if(terminal_column < 0){
                                terminal_column = VGA_WIDTH-1;
                                if(--terminal_row < 0){
                                    terminal_row = 0;
                                }
                            }
                        }
                        break;
                    case VK_ENTER:
                    {
                        terminal_putchar(keyevent->key);
                        char trimmedCommand[commandLength];
                        for(int i = 0; i < commandLength; i++){
                            trimmedCommand[i] = Command[i];
                        }
                        HandleCommand(trimmedCommand, commandLength);
                        commandLength = 0;
                    }
                        break;
                    default:
                        terminal_putchar(keyevent->key);
                        Command[commandLength] = keyevent->key;
                        commandLength++;
                        break;
                }
            }
        }*/
    }
}
extern "C" void kernel_main(void) 
{
	/* Initialize terminal interface */
	terminal_initialize();
    
    //Initialize the PIT
    Port8Bit DataPort(PIT_DATA_PORT);
    Port8Bit CommandPort(PIT_COMMAND_PORT);
    int divisor = 1193180 / 100;
    CommandPort.Write(0x36);
    DataPort.Write(divisor & 0xFF);
    DataPort.Write(divisor >> 8);
 
	/* Newline support is left as an exercise. */
	terminal_writestring("Welcome, to Project Jupiter!\n");
    terminal_writestring("Version 0.1\n");
    initializeSerialAsOutputLog();
    printlnDebugSerial("Initialized Serial Port");
    
    printlnDebugSerial("Initializing Dynamic Memory Management");
    MemoryManager memoryManager(10*1024*1024, 64*1024*1024 - 10*1024*1024 - 10*1024);
    printlnDebugSerial("Dynamic Memory Management initialized");
    
    
    printlnDebugSerial("Initializing GDT");
    GlobalDescriptorTable* gdt = new GlobalDescriptorTable();
    printlnDebugSerial("GDT initialized");
        
    EventManager* eventManager = new EventManager();
    TaskManager* taskManager = new TaskManager();
    Task* task1 = new Task(gdt, Shell);
    taskManager->AddTask(task1);
    
    printlnDebugSerial("Initializing IDT");
    InterruptManager* interrupts = new InterruptManager((uint16_t)0x20, gdt, taskManager);
    KeyboardDriver* keyboard = new KeyboardDriver(interrupts);
    interrupts->Activate();

    
    while(1);
}
