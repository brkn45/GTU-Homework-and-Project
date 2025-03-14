 
#ifndef __MYOS__MULTITASKING_H
#define __MYOS__MULTITASKING_H

#include <common/types.h>
#include <gdt.h>

namespace myos
{
    
    struct CPUState
    {
        common::uint32_t eax;
        common::uint32_t ebx;
        common::uint32_t ecx;
        common::uint32_t edx;

        common::uint32_t esi;
        common::uint32_t edi;
        common::uint32_t ebp;

        /*
        common::uint32_t gs;
        common::uint32_t fs;
        common::uint32_t es;
        common::uint32_t ds;
        */
        common::uint32_t error;

        common::uint32_t eip;
        common::uint32_t cs;
        common::uint32_t eflags;
        common::uint32_t esp;
        common::uint32_t ss;        
    } __attribute__((packed));
    
    enum ProcessState{Ready,Wait,Finish,Runing};
    class Task
    {
    friend class TaskManager;
    private:
        common::uint8_t stack[4096]; // 4 KiB
        CPUState* cpustate;
        common::uint32_t pid =-1;
        common::uint32_t Ppid =-1;
        common::int32_t waitpPidProcess =-99;
        ProcessState processState = Ready;
        int processPriortiy =1;
        GlobalDescriptorTable *gdt;
    public:
        Task(GlobalDescriptorTable *gdt, void entrypoint());
        Task(GlobalDescriptorTable *gdt,int priority ,void entrypoint());
        void setPriorty(int num);
        int getPriorty();
        ~Task();
    };
    
    
    class TaskManager
    {
    private:
        Task *tasks[256];
        int numTasks;
        int currentTask;
        TaskManager *taskManager;
        GlobalDescriptorTable *gdt;
        //Task * readyQueue[256];
    public:
        TaskManager();
        ~TaskManager();
        bool AddTask(Task* task);
        CPUState* Schedule(CPUState* cpustate);
        common::uint32_t getCurrentTaskPid();
        bool setCurrentTaskFinished(CPUState* cpustate);
        bool parentProcessWaitAllChild(CPUState* cpustate);
        CPUState* waitOneProcess(CPUState* cpustate);
        int getProcessIndex(int pid);
        int makeFork(CPUState* cpustate);
        CPUState* makeExec(CPUState* cpustate);
        void printProcessTable();
        void makeReadyQueue();
        CPUState* prioritySchedule(CPUState* cpustate);
        void prioritySort();
        int setPriorityTaskManager(CPUState* cpustate);
        common::uint32_t lowerLevelSchedule(common::uint32_t esp);
        
    };
    
    
    
}


#endif