
#include "memorymanagement.h"

MemoryManager* MemoryManager::activeMemoryManager = 0;
    
MemoryManager::MemoryManager(size_t start, size_t size){
    activeMemoryManager = this;
    
    if(size < sizeof(MemoryChunk)){
        first = 0;
    }else{
        first = (MemoryChunk*)start;
        
        first->allocated = false;
        first->prev = 0;
        first->next = 0;
        first->size = size - sizeof(MemoryChunk);
    }
}

MemoryManager::~MemoryManager(){
    if(activeMemoryManager == this)
        activeMemoryManager = 0;
}
    
void* MemoryManager::malloc(size_t size){
    
}

void MemoryManager::free(void* ptr){
    
}

void* operator new(unsigned size){
    
}

void* operator new[](unsigned size){
    
}

void* operator new(unsigned size, void* ptr){
    
}

void* operator new[](unsigned size, void* ptr){
    
}

void operator delete(void* ptr){
    
}

void operator delete[](void* ptr){
    
}
