
#include "ide.h"

void terminal_writestring(const char* data);
void printDecimal(uint32_t dec);

IDEDriver::IDEDriver(uint32_t bar0, uint32_t bar1, uint32_t bar2, uint32_t bar3, uint32_t bar4, InterruptManager* interupts){
    
    AdvancedTechnologyAttachment* disk = new AdvancedTechnologyAttachment( bar0 == 0x00 || bar0 == 0x01 ? 0x1F0 : bar0, bar1 == 0x00 || bar1 == 0x01 ? 0x3F6 : bar1, true);
    if(disk->Identify()){
        disks[0] = disk;
    }
    
    disk = new AdvancedTechnologyAttachment( bar0 == 0x00 || bar0 == 0x01 ? 0x1F0 : bar0, bar1 == 0x00 || bar1 == 0x01 ? 0x3F6 : bar1, false);
    if(disk->Identify()){
        disks[1] = disk;
    }
    
    disk = new AdvancedTechnologyAttachment( bar2 == 0x00 || bar2 == 0x01 ? 0x170 : bar2, bar3 == 0x00 || bar3 == 0x01 ? 0x376 : bar3, true);
    if(disk->Identify()){
        disks[2] = disk;
    }
    
    disk = new AdvancedTechnologyAttachment( bar2 == 0x00 || bar2 == 0x01 ? 0x170 : bar2, bar3 == 0x00 || bar3 == 0x01 ? 0x376 : bar3, false);
    if(disk->Identify()){
        disks[3] = disk;
    }
    
}

IDEDriver::~IDEDriver(){
    
}
    
void IDEDriver::PrintIDEInfo(){
    for(int i = 0; i < 4; i++){
        if(disks[i] == 0)
            continue;
        terminal_writestring("Drive");
        printDecimal(i);
        terminal_writestring(" OK.\n");
        
    }
}
