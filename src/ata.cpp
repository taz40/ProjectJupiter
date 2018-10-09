
#include "ata.h"

void terminal_writestring(const char* data);
void printDecimal(uint32_t dec);
void printHex(uint32_t hex);

AdvancedTechnologyAttachment::AdvancedTechnologyAttachment(uint16_t portBase, bool master)
: dataPort(portBase),
    errorPort(portBase + 0x1),
    sectorCountPort(portBase + 0x2),
    lbaLowPort(portBase + 0x3),
    lbaMidPort(portBase + 0x4),
    lbaHighPort(portBase + 0x5),
    devicePort(portBase + 0x6),
    commandPort(portBase + 0x7),
    controlPort(portBase + 0x206){
    bytesPerSector = 112;
    this->master = master;
}

AdvancedTechnologyAttachment::~AdvancedTechnologyAttachment(){
    
}
    
void AdvancedTechnologyAttachment::Identify(){
    devicePort.Write(master ? 0xA0 : 0xB0);
    controlPort.Write(0);
    
    devicePort.Write(0xA0);
    uint8_t status = commandPort.Read();
    if(status == 0xFF){
        terminal_writestring("No Device\n");
        return;
    }
    
    devicePort.Write(master ? 0xA0 : 0xB0);
    sectorCountPort.Write(0);
    lbaLowPort.Write(0);
    lbaMidPort.Write(0);
    lbaHighPort.Write(0);
    commandPort.Write(0xEC);
    
    status = commandPort.Read();
    if(status == 0x00){
        terminal_writestring("No Device\n");
        return;
    }
    
    while(((status & 0x80) == 0x80)
        && ((status & 0x01) != 0x01))
        status = commandPort.Read();
    
    if(status & 0x01){
        terminal_writestring("Error\n");
        return;
    }
    
    for(uint16_t i = 0; i < 256; i++){
        uint16_t data = dataPort.Read();
        printHex(data);
        terminal_writestring(" ");
    }
    terminal_writestring("\n");
    
    
    
}

void AdvancedTechnologyAttachment::Read28(uint32_t sectorNumber){
    
}

void AdvancedTechnologyAttachment::Write28(uint32_t sector, uint8_t* data, int count){
    
}

void AdvancedTechnologyAttachment::Flush(){
    
}
