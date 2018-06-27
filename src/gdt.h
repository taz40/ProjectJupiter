#ifndef __GDT_H
#define __GDT_H

#include "types.h"

class GlobalDescriptorTable{
public:
    class SegmentDescriptor{
    private:
        uint16_t LimitLow;
        uint16_t BaseLow;
        uint8_t BaseMid;
        uint8_t Access;
        uint8_t LimitHi;
        uint8_t BaseHi;
    public:
        SegmentDescriptor(uint32_t base, uint32_t limit, uint8_t type);
        uint32_t Base();
        uint32_t Limit();
    } __attribute__((packed));
private:
    SegmentDescriptor nullSegment;
    SegmentDescriptor unusedSegment;
    SegmentDescriptor codeSegment;
    SegmentDescriptor dataSegment;
public:
    
    GlobalDescriptorTable();
    ~GlobalDescriptorTable();
    
    uint16_t CodeSegment();
    uint16_t DataSegment();
    
};

#endif
