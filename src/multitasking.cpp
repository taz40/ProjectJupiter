#include "multitasking.h"

Task::Task(GlobalDescriptorTable* gdt, void entrypoint()){
    cpustate = (CPUState*)(stack + 4096 - sizeof(CPUState));
    
    cpustate->eax = 0;
    cpustate->ebx = 0;
    cpustate->ecx = 0;
    cpustate->edx = 0;
    
    cpustate->esi = 0;
    cpustate->edi = 0;
    cpustate->ebp = 0;
    
    cpustate->eip = (uint32_t)entrypoint;
    cpustate->cs = gdt->CodeSegment();
    
    cpustate->eflags = 0x202;
}

Task::~Task(){
}

TaskManager::TaskManager(){
    taskListInUse = false;
    numTasks = 0;
    currentTask = -1;
}

TaskManager::~TaskManager(){
}

bool TaskManager::AddTask(Task* task){
    while(taskListInUse);
    taskListInUse = true;
    if(numTasks >= 256)
        return false;
    tasks[numTasks++] = task;
    taskListInUse = false;
    return true;
}

void TaskManager::RemoveTask(Task* task){
    int index = -1;
    for(int i = 0; i < numTasks; i++){
        if(tasks[i] == task){
            index = i;
            break;
        }
    }
    if(index == -1)
        return;
    while(taskListInUse);
    for(int x = index+1; x < numTasks; x++){
        tasks[x-1] = tasks[x]; 
    }
    numTasks--;
    taskListInUse = false;
}

CPUState* TaskManager::Schedule(CPUState* cpustate){
    if(numTasks <= 0)
        return cpustate;
    
    if(currentTask >= 0)
        tasks[currentTask]->cpustate = cpustate;
    
    if(++currentTask >= numTasks)
        currentTask %= numTasks;
    return tasks[currentTask]->cpustate;
}
