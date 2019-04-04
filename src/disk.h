#ifndef __DISK_H
#define __DISK_H

#include "driver.h"
#include "types.h"

class Disk : public Driver{
private:
    static Disk** disks;
    static uint16_t diskCount;

public:
    virtual uint8_t* Read(uint32_t sectorNumber);
    virtual void Write(uint32_t sectorNumber, uint8_t* data, int count);

    static void Add(Disk* disk);
    static Disk* GetDisk(uint16_t disk);
};

#endif