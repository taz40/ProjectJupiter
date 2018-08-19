#include "pci.h"

PeripheralComponentInterconnectController::PeripheralComponentInterconnectController()
:dataPort(0xCFC), commandPort(0xCF8){
    
}

PeripheralComponentInterconnectController::~PeripheralComponentInterconnectController(){
    
}

uint32_t PeripheralComponentInterconnectController::Read(uint16_t bus, uint16_t device, uint16_t function, uint32_t registeroffset){
    uint32_t id = 
        0x1 << 31
        | ((bus & 0xFF) << 16)
        | ((device & 0x1F) << 11)
        | ((function & 0x07) << 8)
        | ((registeroffset & 0xFC);
        
        
}

void PeripheralComponentInterconnectController::Write(uint16_t bus, uint16_t device, uint16_t function, uint32_t regtisteroffset, uint32_t value){
    uint32_t id = 
        0x1 << 31
        | ((bus & 0xFF) << 16)
        | ((device & 0x1F) << 11)
        | ((function & 0x07) << 8)
        | ((registeroffset & 0xFC);
        
        
}
