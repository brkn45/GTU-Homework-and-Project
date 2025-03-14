
#include <multitasking.h>

using namespace myos;
using namespace myos::common;

void printf(char* str);
void printfHex(uint8_t);
void printfInt(common::uint32_t);

Task::Task(GlobalDescriptorTable *gdt, void entrypoint())
{
    cpustate = (CPUState*)(stack + 4096 - sizeof(CPUState));
    
    cpustate -> eax = 0;
    cpustate -> ebx = 0;
    cpustate -> ecx = 0;
    cpustate -> edx = 0;

    cpustate -> esi = 0;
    cpustate -> edi = 0;
    cpustate -> ebp = 0;
    
    /*
    cpustate -> gs = 0;
    cpustate -> fs = 0;
    cpustate -> es = 0;
    cpustate -> ds = 0;
    */
    
    // cpustate -> error = 0;    
   
    // cpustate -> esp = ;
    cpustate -> eip = (uint32_t)entrypoint;
    cpustate -> cs = gdt->CodeSegmentSelector();
    // cpustate -> ss = ;
    cpustate -> eflags = 0x202;
    
    this->gdt = gdt;
}

Task::Task(GlobalDescriptorTable *gdt,int priorty ,void entrypoint())
{
    cpustate = (CPUState*)(stack + 4096 - sizeof(CPUState));
    
    cpustate -> eax = 0;
    cpustate -> ebx = 0;
    cpustate -> ecx = 0;
    cpustate -> edx = 0;

    cpustate -> esi = 0;
    cpustate -> edi = 0;
    cpustate -> ebp = 0;
    
    /*
    cpustate -> gs = 0;
    cpustate -> fs = 0;
    cpustate -> es = 0;
    cpustate -> ds = 0;
    */
    
    // cpustate -> error = 0;    
   
    // cpustate -> esp = ;
    cpustate -> eip = (uint32_t)entrypoint;
    cpustate -> cs = gdt->CodeSegmentSelector();
    // cpustate -> ss = ;
    cpustate -> eflags = 0x202;
    
    this->gdt = gdt;
    this->processPriortiy = priorty;
}

Task::~Task()
{
}

void Task::setPriorty(int num){
    if(num<0 || num>11){
        
        printf("Priorty size must be between 1 and 10\n");
        return;
    }
    processPriortiy = num;
 }  
int Task::getPriorty(){
    
    return processPriortiy;
 }      
TaskManager::TaskManager()
{
    numTasks = 0;
    currentTask = -1;
}

TaskManager::~TaskManager()
{
}

bool TaskManager::AddTask(Task* task)
{
    
    if(numTasks >= 256)
        return false;
    task->pid = numTasks +1;
    
    
    task->Ppid =0;
    task->processState = Ready;    
    tasks[numTasks++] = task;
    
    return true;
}
int TaskManager::getProcessIndex(int pid){
    int i=0;
    while(i<numTasks){
        if(tasks[i]->pid == pid){
            return i;
        }
        i++;
    }
    return -1;
}

CPUState* TaskManager::Schedule(CPUState* cpustate)
{
    
    if(numTasks <= 0)
        return cpustate;
    if(currentTask >= 0)
        tasks[currentTask]->cpustate = cpustate;
    
    currentTask++;    
    if(currentTask >= numTasks)
        currentTask %= numTasks;
    int i=0;
    
   
    if(tasks[currentTask]->processState != Ready){
        //eğer parent process wait ise
        if(tasks[currentTask]->processState == Wait &&tasks[currentTask]->waitpPidProcess == -1){
            int i=0;
            int readyControllFlag =0;
            while(i<numTasks){
                if(tasks[i]->Ppid == tasks[currentTask]-> pid){
                    if(tasks[i]->processState == Ready){
                        readyControllFlag = 1;
                        break;
                    }
                }
                i++;
            }
            if(readyControllFlag == 0){
                tasks[currentTask]->processState = Ready;
            }
        }
        else if(tasks[currentTask]->processState == Wait && tasks[currentTask]->waitpPidProcess != -99){
            int processIndex = getProcessIndex(tasks[currentTask]->waitpPidProcess); 
            if(tasks[processIndex]->processState == Finish){
                tasks[currentTask]->processState = Ready;
            }
        }
        //if there arent ready process
        int flag= 0;
        while(tasks[currentTask]->processState != Ready ){
        currentTask++;
        if(currentTask >= numTasks){
            currentTask %= numTasks;
            flag++;
            
            if(flag == 2){
                printProcessTable();
                printf("All Process Finished\n");
                while(true);
                break;
            }
            }
        }
    }
    //printProcessTable();
    return tasks[currentTask]->cpustate;
       
}

CPUState* TaskManager::prioritySchedule(CPUState* cpustate)
{
    if (numTasks <= 0)
        return cpustate;
    if (currentTask >= 0)
        tasks[currentTask]->cpustate = cpustate;
        
    for(int i=numTasks/2; i< numTasks; i++){
        if(tasks[i]->processState == Ready){
            tasks[i]->setPriorty(tasks[i]->getPriorty()+1);
        }
        
    }
    prioritySort();
    int highestPriorityIndex = -1;
    int highestPriority = -1;

    for (int i = 0; i < numTasks; i++)
    {
        if (tasks[i]->processState == Ready && tasks[i]->getPriorty() > highestPriority){
            highestPriority = tasks[i]->getPriorty();
            highestPriorityIndex = i;
        }
    }
    if (highestPriorityIndex != -1)
    {
        currentTask = highestPriorityIndex;
    }

    if (currentTask >= 0)
    {
        tasks[currentTask]->processState = Ready;
        return tasks[currentTask]->cpustate;
    }
    
    return tasks[currentTask]->cpustate;
}


void TaskManager::prioritySort()
{
    for (int i = 0; i < numTasks - 1; i++)
    {
        for (int j = 0; j < numTasks - i - 1; j++)
        {
            if (tasks[j]->getPriorty() < tasks[j + 1]->getPriorty())
            {
                Task* temp = tasks[j];
                
                
                tasks[j] = tasks[j + 1];
                tasks[j + 1] = temp;
            }
        }
    }
    
    
}

common::uint32_t TaskManager::getCurrentTaskPid(){
    
    return tasks[currentTask]->pid;
}    

bool TaskManager::setCurrentTaskFinished(CPUState* cpustate){
    tasks[currentTask]->cpustate = cpustate;
    tasks[currentTask]->processState = Finish;
   
    int i=0;
        
    return true;
}

bool TaskManager::parentProcessWaitAllChild(CPUState* cpustate){
    
    
    tasks[currentTask]->cpustate = cpustate;
    tasks[currentTask]->waitpPidProcess = -1;
    tasks[currentTask]->processState = Wait;
    return true;
    
}

CPUState* TaskManager::waitOneProcess(CPUState* cpustate){
    int pid = cpustate->ebx;
    
    if(numTasks<pid){
        return cpustate;
    }
    
    int index = getProcessIndex(pid);
    if(index == -1){
        return cpustate;
    }
    
    if(tasks[index]->processState == Finish){
        return cpustate;
    }
    
    if(tasks[currentTask]->pid == pid ){
        return cpustate;
    }
    
    tasks[currentTask]->cpustate = cpustate;
    tasks[currentTask]->waitpPidProcess = cpustate->ebx;
    tasks[currentTask]->processState = Wait;
   
    return tasks[currentTask]->cpustate;
    
}

int TaskManager::makeFork(CPUState* cpustate){
    
    if(numTasks >= 256)
        return 0;
   
    tasks[numTasks]= new Task(gdt, nullptr);
    
    for (int i = 0; i < sizeof(tasks[currentTask]->stack); i++)
    {
        tasks[numTasks]->stack[i]=tasks[currentTask]->stack[i];
    }
    
    
    common::uint32_t currentTaskOffset=(((common::uint32_t)cpustate - (common::uint32_t) tasks[currentTask]->stack));
    tasks[numTasks]->cpustate=(CPUState*)(((common::uint32_t) tasks[numTasks]->stack) + currentTaskOffset);
 
    //Burada ECX' yeni taskın process id'sini atıyorum. Syscall'a return edebilmek için.
    tasks[numTasks]->cpustate->ecx = 0;
    tasks[numTasks]->cpustate->ebp = tasks[numTasks]->stack + cpustate->ebp - tasks[currentTask]->stack;
    tasks[numTasks]->processState=Ready;
    tasks[numTasks]->Ppid=tasks[currentTask]->pid;
    tasks[numTasks]->pid=numTasks+1;
    tasks[numTasks]->setPriorty(tasks[currentTask]->getPriorty());

    numTasks++;
    
    return tasks[currentTask]->pid;
}

CPUState* TaskManager::makeExec(CPUState* cpustate){
   
    //yeni yer açmadanda çalışıyor
    tasks[currentTask]->cpustate = (CPUState*)(tasks[currentTask]->stack + 4096 - sizeof(CPUState));

    //entry point is in ebx
    tasks[currentTask]->cpustate -> eip =  cpustate -> ebx;
    //tasks[currentTask]->cpustate -> ecx = taskManager[currentTask].getCurrentTaskPid();
    tasks[currentTask]->cpustate -> eax = 0;
    tasks[currentTask]->cpustate -> ebx = 0;
    tasks[currentTask]->cpustate -> edx = 0;

    tasks[currentTask]->cpustate -> esi = 0;
    tasks[currentTask]->cpustate -> edi = 0;
    tasks[currentTask]->cpustate -> ebp = 0;
    tasks[currentTask]->processState = Ready;
    tasks[currentTask]->cpustate->cs = gdt->CodeSegmentSelector();
    tasks[currentTask]->cpustate-> eflags = 0x202;

    return tasks[currentTask]->cpustate;
}

int TaskManager::setPriorityTaskManager(CPUState* cpustate){
    int pid = cpustate->ebx;
    int priority= cpustate->edx;
    
    
    int index = getProcessIndex(pid);
    if(index == -1){
        cpustate->ecx = -1;
        return -1;
    }
    cpustate->ecx = 1;
    
    tasks[index]->setPriorty(priority);
    
    return 0;
}


common::uint32_t TaskManager::lowerLevelSchedule(common::uint32_t esp){
    CPUState* cpustate = (CPUState*) esp;
    
    if (numTasks <= 0)
        return (common::uint32_t) cpustate;
    if (currentTask >= 0)
        tasks[currentTask]->cpustate = cpustate;

    prioritySort();
    for(int i =numTasks-1; i> -1 ; i--){
        if(tasks[i]->processState == Ready){
            currentTask = i;
            break;
        }
    } 
    
    return (common::uint32_t) tasks[currentTask]->cpustate ;
}


void TaskManager::printProcessTable() {
            printf( "number of tasks: " ); printfInt( numTasks);printf("");
            printf( "    Current tasks: " );  printfInt( currentTask+1);printf("\n");
            printf( "-----------------------------------------------------------------------\n");
            printf( "| PID | Parent PID | Priority        | EIP             | State        |\n");
            printf( "-----------------------------------------------------------------------\n");
            
            for (int i = 0; i < numTasks; i++) {
                Task* task = tasks[i];
                  // Null kontrolü

                char* state = "Unknown";
                switch (task->processState) {
                    case Ready:   state = "Ready";   break;
                    case Wait:    state = "Wait";    break;
                    case Finish:  state = "Finish";  break;
                    
                }

                printf( "| "); printfInt( task->pid); 
                        printf("   | "); printfInt( task->Ppid);
                        printf( "         | " );printfInt(task->getPriorty());
                        printf( "                | " ); printfInt(task->cpustate->eip );
                        
                        if(currentTask == i &&task->processState == Ready  ){
                        printf( "          |"); printf("Running");
                        }
                        else{
                        printf( "          |"); printf(state);
                        }  
                          
                          
                        printf( "       \n");
            }
            
            printf( "----------------------------------------------------------------------\n");

   
}         

