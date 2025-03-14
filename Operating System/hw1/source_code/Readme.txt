### ReadMe.txt

#### Gebze Technical University
#### Department Of Computer Engineering
#### CSE 312 / CSE 504 Spring 2024
#### Operating Systems - Homework #01

---

### Part A

#### Task Description
For Part A, the task was to implement essential POSIX system calls including `fork`, `waitpid`, and `execve`. Additionally, we needed to support multitasking by loading multiple programs into memory and managing them using a Process Table. The kernel should handle interrupts and manage context switching using Round Robin scheduling.

#### Implementation Steps
1. **System Calls Implemented:**
   - `fork`: To create new processes.
   - `waitpid`: To wait for state changes in child processes.
   - `execve`: To execute a new program in the current process.

2. **Process Table:**
   - Developed a structure to store information about processes, such as their states and identifiers.

3. **Memory Management:**
   - Enabled loading multiple programs into memory.
   - Implemented memory allocation and deallocation procedures.

4. **Interrupt Handling:**
   - Integrated the capability to handle interrupts and perform context switches using Round Robin scheduling.

5. **Testing Programs:**
   - Collatz sequence computation
   - Binary Search
   - Linear Search
   - Long-running computation program

#### Execution Instructions
- Compile the source files using the provided Makefile.
- Run the compiled kernel.
- The kernel will automatically start the init process and load the specified programs.

---

### Part B

#### Task Description
For Part B, the focus was on implementing different scheduling strategies including Round Robin and Priority-Based (Preemptive) Scheduling. The init process should load programs into memory according to different strategies.

#### Implementation Steps
1. **Round Robin Scheduling:**
   - Implemented to switch processes on every timer interrupt.
   - Process Table information is printed on each context switch.

2. **Priority-Based Scheduling:**
   - Implemented Preemptive Priority Scheduling.
   - Processes are scheduled based on their priority levels.

3. **Strategies:**
   - **First Strategy:** Load one program 10 times.
   - **Second Strategy:** Load two out of four programs, each 3 times.
   - **Third Strategy:** Init process initializes the Process Table and ready queue, dynamically adjusts priorities.

#### Execution Instructions
- Compile the source files using the provided Makefile.
- Run the compiled kernel.
- The init process will load and schedule the programs according to the implemented strategies.

---

### Part C

#### Task Description
For Part C, the tasks involved handling interactive input events and implementing different input handling strategies such as Random Process Spawning and Interactive Input Priority.

#### Implementation Steps
1. **Random Process Spawning:**
   - Processes are spawned randomly and react to interactive inputs like mouse clicks and keyboard presses.

2. **Interactive Input Priority Strategy:**
   - Processes are assigned priorities based on the type of interactive input they handle.
   - High-priority tasks handle critical inputs, while low-priority tasks handle non-critical inputs.

3. **Interactive Input Handling:**
   - Implemented handlers to switch tasks based on keyboard and mouse events.

#### Execution Instructions
- Compile the source files using the provided Makefile.
- Run the compiled kernel.
- Interact with the running processes using the keyboard and mouse as specified in the implementation.
-   "make run" is start to virtual machine
---

### General Instructions
1. **Submission Requirements:**
   - Submit all source files.
   - Include this ReadMe.txt with execution instructions.
   - Submissions without Makefile, Report, and ReadMe.txt will not be evaluated.

2. **Important Notes:**
   - Start early to avoid last-minute issues.
   - This is not a group project; do not share your answers.
   - Your report should include design decisions, structures, comments, codes, and results for each strategy with screenshots.
   - For grading, syscall implementation and strategy implementations are crucial.
   - Write comments on critical lines of your code.
   - After the deadline, be prepared to explain your project during a demonstration session.