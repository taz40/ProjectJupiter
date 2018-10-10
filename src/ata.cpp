
#include "ata.h"

void terminal_writestring(const char* data);
void printDecimal(uint32_t dec);
void printHex(uint32_t hex);

AdvancedTechnologyAttachment::AdvancedTechnologyAttachment(uint16_t dataPortBase, uint16_t commandPortBase, bool master)
: dataPort(dataPortBase),
    errorPort(dataPortBase + 0x1),
    sectorCountPort(dataPortBase + 0x2),
    lbaLowPort(dataPortBase + 0x3),
    lbaMidPort(dataPortBase + 0x4),
    lbaHighPort(dataPortBase + 0x5),
    devicePort(dataPortBase + 0x6),
    commandPort(dataPortBase + 0x7),
    controlPort(commandPortBase){
    bytesPerSector = 112;
    this->master = master;
}

AdvancedTechnologyAttachment::~AdvancedTechnologyAttachment(){
    
}
    
bool AdvancedTechnologyAttachment::Identify(){
    devicePort.Write(master ? 0xA0 : 0xB0);
    controlPort.Write(0);
    
    devicePort.Write(0xA0);
    uint8_t status = commandPort.Read();
    if(status == 0xFF){
        //terminal_writestring("No Device\n");
        return false;
    }
    
    devicePort.Write(master ? 0xA0 : 0xB0);
    sectorCountPort.Write(0);
    lbaLowPort.Write(0);
    lbaMidPort.Write(0);
    lbaHighPort.Write(0);
    commandPort.Write(0xEC);
    
    status = commandPort.Read();
    if(status == 0x00){
        //terminal_writestring("No Device\n");
        return false;
    }
    
    while(((status & 0x80) == 0x80)
        && ((status & 0x01) != 0x01))
        status = commandPort.Read();
    
    if(status & 0x01){
        //terminal_writestring("Error\n");
        return false;
    }
    
    for(uint16_t i = 0; i < 256; i++){
        uint16_t data = dataPort.Read();
        //printHex(data);
        //terminal_writestring(" ");
    }
    //terminal_writestring("\n");
    
    return true;
    
}

void AdvancedTechnologyAttachment::Read28(uint32_t sectorNumber){
    
}

void AdvancedTechnologyAttachment::Write28(uint32_t sector, uint8_t* data, int count){
    
}

void AdvancedTechnologyAttachment::Flush(){
    
}
