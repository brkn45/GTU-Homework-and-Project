
#include <syscalls.h>
 
using namespace myos;
using namespace myos::common;
using namespace myos::hardwarecommunication;
 
SyscallHandler::SyscallHandler(InterruptManager* interruptManager, uint8_t InterruptNumber)
:    InterruptHandler(interruptManager, InterruptNumber  + interruptManager->HardwareInterruptOffset())
{
}

SyscallHandler::~SyscallHandler()
{
}
enum SYSCALLS{EXIT, GETPID, WAITPIDALL,WAITPIDONE, FORK, EXECVE,PRIORITY};

void printf(char*);
void printfInt(common::uint32_t);

int myos::getPid()
{
    int pid=-1;
    asm("int $0x80" : "=c" (pid) : "a" (SYSCALLS::GETPID));
    return pid;
}

int myos::waitpid(int pid){
    int rValue = 0;
    int tmpPid = pid;
    if(pid == -1){
        asm("int $0x80" : "=c" (rValue) : "a" (SYSCALLS::WAITPIDALL));
    
    }
    else{
        asm("int $0x80" 
    : "=c" (rValue)            // çıktı: ecx kaydedicisine sonuç değeri
    : "a" (SYSCALLS::WAITPIDONE), "b" (pid)  // girdi: eax'e syscall numarası, ebx'e pid değeri
    :);
    }
    return rValue;
}

int myos::exit(){
    int status =-1;
    asm("int $0x80" : "=c" (status) : "a" (SYSCALLS::EXIT));
    return status;
}

int myos::fork(){
    int pid =-1;
    asm("int $0x80" : "=c" (pid) : "a" (SYSCALLS::FORK));
    return pid;

}

int myos::execve(void entrypoint()){
    int result;
    asm("int $0x80" : "=c" (result) : "a" (SYSCALLS::EXECVE), "b" ((uint32_t)entrypoint) :);
    return result;
}

int myos::setPriority(int which, int prio){
    int result=-1;
    asm("int $0x80" : "=c" (result) : "a" (SYSCALLS::PRIORITY), "b" (which), "d" (prio) : );
    return result;
}
uint32_t SyscallHandler::HandleInterrupt(uint32_t esp)
{
    CPUState* cpu = (CPUState*)esp;
    

    switch(cpu->eax)
    {
        case GETPID:
            cpu->ecx = interruptManager->getPidInterrupt();
            break;
        case FORK:
            cpu->ecx=interruptManager->createProcess(cpu);
            //return InterruptHandler::HandleInterrupt(esp);
            break;
        case EXECVE:
            esp =  (uint32_t) interruptManager->interruptExec(cpu);
            //return InterruptHandler::HandleInterrupt(esp);
            break;
        case WAITPIDALL:
            interruptManager->setWaitProcessForAllChild(cpu);
            esp =interruptManager->scheduleTask(cpu);
            break;
            
        case WAITPIDONE:
            esp = (uint32_t) interruptManager->setOneProcess(cpu);
            esp =interruptManager->scheduleTask((CPUState*)esp);
            
            break;
        case EXIT:
            if(interruptManager->exitInterrupt(cpu) == true){
                cpu->ecx = 0;
                esp =interruptManager->scheduleTask(cpu);
                //return InterruptHandler::HandleInterrupt(esp);
            }
            break; 
        case PRIORITY:
            cpu->eax= interruptManager->setPriortyIM(cpu);
            esp = (uint32_t)cpu;
            break;       
        default:
            break;
    }

    
    return esp;
}

