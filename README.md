# OS_Assignments

Advanced Systems Programming Assignments
This repository contains three assignments focusing on systems programming concepts in Linux using C, including shell development, threading, scheduling, process management, interprocess communication, and kernel modules.

## Assignments Overview

### **A1: Simple Linux/Unix Shell**
This assignment involves designing a basic command-line shell that can handle both **internal** and **external** commands using **Linux system calls** and **POSIX threads**.

#### **Task 1: Shell Implementation**
- Implements three **internal commands**:  
  - `cd` (change directory)  
  - `echo` (print message)  
  - `pwd` (print working directory)  
- Supports five **external commands** through custom programs:  
  - `ls` (list directory contents)  
  - `cat` (concatenate and display files)  
  - `date` (display system date/time)  
  - `rm` (remove files)  
  - `mkdir` (create directories)  
- Uses `fork()`, `exec()` family functions, and `wait()` for process creation and execution.  

#### **Task 2: Thread-Based Execution**
- Implements an alternative version of the shell using **POSIX threads** (`pthread_create()`) instead of `fork()`, and `system()` instead of `exec()`.  
- The thread-based execution is triggered when a command is followed by `&t`.  

---

### **A2: Linux Thread and Process Scheduling**
This assignment explores **thread scheduling** and **process scheduling** in Linux.

#### **Part 1: Thread Scheduling**
- Launches three threads running independent counting functions (`countA()`, `countB()`, `countC()`).  
- Uses different scheduling policies:  
  - **Thread 1 (Thr-A):** `SCHED_OTHER` (default Linux scheduler).  
  - **Thread 2 (Thr-B):** `SCHED_RR` (round-robin scheduling).  
  - **Thread 3 (Thr-C):** `SCHED_FIFO` (first-in, first-out scheduling).  
- Measures execution time for each scheduling policy using `clock_gettime()`.  
- Benchmarks different scheduling priorities using `pthread_setschedparam()`.  
- Generates histograms comparing execution time across different policies and priorities.  

#### **Part 2: Process Scheduling**
- Spawns three processes using `fork()` and `execl()`.  
- Each process compiles a **minimal Linux kernel** using separate bash scripts.  
- Measures execution time of each process using `clock_gettime()`.  
- Uses `waitpid()` to synchronize process completion.  

---

### **A3: Advanced Synchronization and Interprocess Communication**
This assignment focuses on **synchronization**, **interprocess communication (IPC)**, and **kernel module development**.

#### **Part 1: Modified Dining Philosophers Problem**
- Implements a **deadlock-free** solution to the classic Dining Philosophers problem using **POSIX threads** and **semaphores**.  
- Implements two approaches:  
  1. **Strict resource ordering** to prevent circular wait conditions.  
  2. **Semaphore-based synchronization**, ensuring philosophers acquire both forks and a sauce bowl before eating.  

#### **Part 2: Interprocess Communication (IPC)**
- Implements two programs (`P1` and `P2`) for message passing:
  - `P1` generates **50 random strings** and sends them in batches of 5.  
  - `P2` acknowledges receipt by returning the highest received **ID** before accepting the next batch.  
- Implements IPC using three methods:
  - **Unix domain sockets**
  - **FIFOs (named pipes)**
  - **Shared memory**  
- Measures and compares execution time for each IPC mechanism.  

#### **Part 3: Linux Kernel Module**
- Implements a **custom kernel module** that introduces a new **system call** to retrieve process information.  
- The system call prints:
  - **Process ID (pid)**
  - **User ID (uid)**
  - **Process Group ID (pgid)**
  - **Command path**  
- The system call functions **only when the module is loaded**, ensuring modularity and safety.  

---

