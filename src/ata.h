#ifndef __ATA_H
#define __ATA_H

#include "port.h"
#include "disk.h"

class AdvancedTechnologyAttachment :  public Disk{
protected:
    Port16Bit dataPort;
    Port8Bit errorPort;
    Port8Bit sectorCountPort;
    Port8Bit lbaLowPort;
    Port8Bit lbaMidPort;
    Port8Bit lbaHighPort;
    Port8Bit devicePort;
    Port8Bit commandPort;
    Port8Bit controlPort;
    bool master;
    uint16_t bytesPerSector;
    uint16_t identifyData[256];
    bool lba48Mode;
    uint8_t udmaModes;
    uint8_t activeUdmaMode;
    bool has80PinCable;
    uint32_t lba28Sectors;
    uint64_t lba48Sectors;
public:
    AdvancedTechnologyAttachment(uint16_t dataPortBase, uint16_t commandPortBase, bool master);
    ~AdvancedTechnologyAttachment();
    
    bool Identify();
    uint8_t* Read28(uint32_t sectorNumber);
    void Write28(uint32_t sector, uint8_t* data, int count);
    void Flush();
    void PrintInfo();

    virtual uint8_t* Read(uint32_t sectorNumber);
    virtual void Write(uint32_t sectorNumber, uint8_t* data, int count);
};

#endif
