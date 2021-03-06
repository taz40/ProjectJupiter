
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
    // devicePort.Write(master ? 0xA0 : 0xB0);
    // controlPort.Write(0);
    
    // devicePort.Write(0xA0);
    // uint8_t status = commandPort.Read();
    // if(status == 0xFF){
    //     terminal_writestring("No Device\n");
    //     return false;
    // }
    
    devicePort.Write(master ? 0xA0 : 0xB0);
    sectorCountPort.Write(0);
    lbaLowPort.Write(0);
    lbaMidPort.Write(0);
    lbaHighPort.Write(0);
    commandPort.Write(0xEC);
    lbaLowPort.Write(0);
    uint8_t status = commandPort.Read();
    if(status == 0x00){
        //terminal_writestring("No Device\n");
        return false;
    }
    
    while(((status & 0x80) == 0x80)
        && ((status & 0x01) != 0x01)){
        status = commandPort.Read();
        //printHex(status);
    }

    if(lbaMidPort.Read() != 0 || lbaHighPort.Read() != 0){
        if(lbaMidPort.Read() == 0x14 && lbaHighPort.Read() == 0xEB){
            //terminal_writestring("ATAPI device\n");
        }else if(lbaMidPort.Read() == 0x3c && lbaHighPort.Read() == 0xc3){
            //terminal_writestring("SATA device\n");
        }else{
            //terminal_writestring("no device\n");
        }

        return false;
    }
    
    // if(status & 0x01){
    //     if(lbaMidPort.Read() != 0 || lbaHighPort.Read() != 0){
    //         terminal_writestring("Not an ATA device\n");
    //         return false;
    //     }
    //     terminal_writestring("Error\n");
    //     return false;
    // }

    status = commandPort.Read();
    while((status & 0x08) != 0x08 && (status & 0x01) != 0x01){
        status = commandPort.Read();
    }

    if((status & 0x01) == 0x01){
        //terminal_writestring("Device Error\n");
        return false;
    }

    for(uint16_t i = 0; i < 256; i++){
        uint16_t data = dataPort.Read();
        identifyData[i] = data;
        //printHex(data);
        //terminal_writestring(" ");
    }
    bytesPerSector = 512;
    lba48Mode = (identifyData[83] & 0x400) == 0x400;
    activeUdmaMode = (identifyData[88] >> 8) & 0xFF;
    udmaModes = (identifyData[88] & 0xFF);
    has80PinCable = (identifyData[93] & 0x800) == 0x800;
    lba28Sectors = ((identifyData[61] & 0xFFFF) << 16) | (identifyData[60] & 0xFFFF);
    lba48Sectors = ((identifyData[103] & 0xFFFF) << 48) | ((identifyData[102] & 0xFFFF) << 32) | ((identifyData[101] & 0xFFFF) << 16) | (identifyData[100] & 0xFFFF);
    //terminal_writestring("OK\n");
    
    return true;
    
}

uint8_t* AdvancedTechnologyAttachment::Read28(uint32_t sectorNumber){
    devicePort.Write((master ? 0xE0 : 0xF0) | ((sectorNumber >> 24) & 0xF) );
    sectorCountPort.Write(1);
    lbaLowPort.Write(sectorNumber & 0xFF);
    lbaMidPort.Write((sectorNumber >> 8) & 0xFF);
    lbaHighPort.Write((sectorNumber >> 16) & 0xFF);
    commandPort.Write(0x20);
    
    uint8_t status = commandPort.Read();
    while((status & 0x8) != 0x8){
        status = commandPort.Read();
    }

    uint8_t* buffer = new uint8_t[512];
    for(int i = 0; i < 256; i++){
        uint16_t tmp = dataPort.Read();
        buffer[i*2] = tmp & 0xFF;
        buffer[(i*2)+1] = (tmp >> 8) & 0xFF;
    }

    return buffer;
    
}

void AdvancedTechnologyAttachment::Write28(uint32_t sectorNumber, uint8_t* data, int count){
    devicePort.Write((master ? 0xE0 : 0xF0) | ((sectorNumber >> 24) & 0xF) );
    sectorCountPort.Write(1);
    lbaLowPort.Write(sectorNumber & 0xFF);
    lbaMidPort.Write((sectorNumber >> 8) & 0xFF);
    lbaHighPort.Write((sectorNumber >> 16) & 0xFF);
    commandPort.Write(0x30);
    
    uint8_t status = commandPort.Read();
    while((status & 0x8) != 0x8){
        status = commandPort.Read();
    }

    for(int i = 0; i < 256; i++){
        uint16_t tmp = 0;
        if(i*2 < count){
            tmp |= data[i*2] & 0xFF;
        }
        if((i*2)+1 < count){
            tmp |= (data[(i*2)+1] << 8) & 0xFF00;
        }
        dataPort.Write(tmp);
    }
    commandPort.Write(0xE7);
}

void AdvancedTechnologyAttachment::Flush(){
    
}

void AdvancedTechnologyAttachment::PrintInfo(){
        terminal_writestring("LBA48: ");
    if(lba48Mode){
        terminal_writestring("True\n");
    }else{
        terminal_writestring("False\n");
    }
    terminal_writestring("UDMA Modes: ");
    printHex(udmaModes);
    terminal_writestring("\nActive UDMA Mode: ");
    printHex(activeUdmaMode);
    terminal_writestring("\n80 Pin Cable: ");
    if(has80PinCable){
        terminal_writestring("True\n");
    }else{
        terminal_writestring("False\n");
    }
    terminal_writestring("LBA28 Sectors: ");
    printDecimal(lba28Sectors);
    terminal_writestring(" (");
    printDecimal(lba28Sectors >> 21);
    terminal_writestring("GB)\n");
    if(lba48Mode){
        terminal_writestring("LBA48 Sectors: ");
        printDecimal(lba48Sectors);
        terminal_writestring(" (");
        printDecimal((4294965248 >> 21) & 0x7FFFFFFFFFF);
        terminal_writestring("GB)\n");
    }
}

uint8_t* AdvancedTechnologyAttachment::Read(uint32_t sectorNumber){
    Read28(sectorNumber);
}

void AdvancedTechnologyAttachment::Write(uint32_t sectorNumber, uint8_t* data, int count){
    return Write28(sectorNumber, data, count);
}