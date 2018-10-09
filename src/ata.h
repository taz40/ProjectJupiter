#ifndef __ATA_H
#define __ATA_H

#include "port.h"
#include "driver.h"

class AdvancedTechnologyAttachment :  public Driver{
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
public:
    AdvancedTechnologyAttachment(uint16_t portBase, bool master);
    ~AdvancedTechnologyAttachment();
    
    void Identify();
    void Read28(uint32_t sectorNumber);
    void Write28(uint32_t sector, uint8_t* data, int count);
    void Flush();
};

#endif
