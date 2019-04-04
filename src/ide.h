#ifndef __IDE_H
#define __IDE_H

#include "driver.h"
#include "ata.h"
#include "interrupts.h"

class IDEDriver : public Driver{
public:
    AdvancedTechnologyAttachment* disks[4];
public:
    IDEDriver(uint32_t bar0, uint32_t bar1, uint32_t bar2, uint32_t bar3, uint32_t bar4, InterruptManager* interupts);
    ~IDEDriver();
    
    void PrintIDEInfo();
    void PrintAllIDEInfo();
};

#endif
