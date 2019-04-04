#include "disk.h"

Disk** Disk::disks = new Disk*[200];
uint16_t Disk::diskCount = 0;

void Disk::Add(Disk* disk){
    disks[diskCount] = disk;
    diskCount++;
}

Disk* Disk::GetDisk(uint16_t disk){
    if(disk >= 0 && disk < diskCount){
        return disks[disk];
    }
    return nullptr;
}

uint8_t* Disk::Read(uint32_t sectorNumber){

}

void Disk::Write(uint32_t sectorNumber, uint8_t* data, int count){

}