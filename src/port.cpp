#include "port.h"

Port::Port(uint16_t portNumber){
    this->portnumber = portNumber;
}

Port::~Port(){
}


Port8Bit::Port8Bit(uint16_t portNumber)
: Port(portNumber){
}

Port8Bit::~Port8Bit(){
}
    
uint8_t Port8Bit::Read(){
    return Read8(portnumber);
}

void Port8Bit::Write(uint8_t data){
    Write8(portnumber, data);
}

Port8BitSlow::Port8BitSlow(uint16_t portNumber)
: Port8Bit(portNumber){
}

Port8BitSlow::~Port8BitSlow(){
}
    
void Port8BitSlow::Write(uint8_t data){
    Write8Slow(portnumber, data);
}

Port16Bit::Port16Bit(uint16_t portNumber)
: Port(portNumber){
}

Port16Bit::~Port16Bit(){
}
    
uint16_t Port16Bit::Read(){
    return Read16(portnumber);
}

void Port16Bit::Write(uint16_t data){
    Write16(portnumber, data);
}


Port32Bit::Port32Bit(uint16_t portNumber)
: Port(portNumber){
}
Port32Bit::~Port32Bit(){
}
    
uint32_t Port32Bit::Read(){
    return Read32(portnumber);
}
void Port32Bit::Write(uint32_t data){
    Write32(portnumber, data);
}
