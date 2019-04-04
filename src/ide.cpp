
#include "ide.h"
#include "disk.h"

void terminal_writestring(const char* data);
void printDecimal(uint32_t dec);

IDEDriver::IDEDriver(uint32_t bar0, uint32_t bar1, uint32_t bar2, uint32_t bar3, uint32_t bar4, InterruptManager* interupts){

    AdvancedTechnologyAttachment* disk1 = new AdvancedTechnologyAttachment( bar0 == 0x00 || bar0 == 0x01 ? 0x1F0 : bar0, bar1 == 0x00 || bar1 == 0x01 ? 0x3F6 : bar1, true);
    if(disk1->Identify()){
        disks[0] = disk1;
        Disk::Add(disk1);
    }

    AdvancedTechnologyAttachment* disk2 = new AdvancedTechnologyAttachment( bar0 == 0x00 || bar0 == 0x01 ? 0x1F0 : bar0, bar1 == 0x00 || bar1 == 0x01 ? 0x3F6 : bar1, false);
    if(disk2->Identify()){
        disks[1] = disk2;
        Disk::Add(disk2);
    }

    AdvancedTechnologyAttachment* disk3 = new AdvancedTechnologyAttachment( bar2 == 0x00 || bar2 == 0x01 ? 0x170 : bar2, bar3 == 0x00 || bar3 == 0x01 ? 0x376 : bar3, true);
    if(disk3->Identify()){
        disks[2] = disk3;
        Disk::Add(disk3);
    }

    AdvancedTechnologyAttachment* disk4 = new AdvancedTechnologyAttachment( bar2 == 0x00 || bar2 == 0x01 ? 0x170 : bar2, bar3 == 0x00 || bar3 == 0x01 ? 0x376 : bar3, false);
    if(disk4->Identify()){
        disks[3] = disk4;
        Disk::Add(disk4);
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

void IDEDriver::PrintAllIDEInfo(){
    for(int i = 0; i < 4; i++){
        if(disks[i] == 0)
            continue;
        terminal_writestring("Drive");
        printDecimal(i);
        terminal_writestring("\n");
        disks[i]->PrintInfo();
        
    }
}
