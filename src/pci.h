#ifndef __PCI_H
#define __PCI_H

#include "port.h"

class PeripheralComponentInterconnectController{
private:
    Port32Bit dataPort;
    Port32Bit commandPort
public:
    PeripheralComponentInterconnectController();
    ~PeripheralComponentInterconnectController();
    
    uint32_t Read(uint16_t bus, uint16_t device, uint16_t function, uint32_t registeroffset);
    void Write(uint16_t bus, uint16_t device, uint16_t function, uint32_t regtisteroffset, uint32_t value);
}

#endif
