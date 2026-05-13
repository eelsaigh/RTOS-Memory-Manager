# Embedded Memory Management Simulator (First-Fit)

A custom Memory Management Unit (MMU) simulator that demonstrates how a Real-Time Operating System (RTOS) handles dynamic memory allocation. 

This repository contains two distinct implementations of the same First-Fit allocation algorithm: a bare-metal approach using manual pointers in C, and an Object-Oriented approach using Java Collections.

## Key Technical Concepts Demonstrated

* **Algorithmic Translation:** Successfully implements the First-Fit allocation and active memory compaction logic across two fundamentally different programming paradigms.
* **C Implementation (Bare-Metal):** Utilizes raw pointers (`*`), `malloc()`, and `free()` to construct a manual linked-list representing the memory heap. Safely handles memory splitting and pointer reassignment during allocation and compaction.
* **Java Implementation (OOP):** Leverages `ArrayList<Block>` and Object-Oriented state management to track Process IDs (PIDs), block sizes, and allocation status.
* **Active Compaction Logic:** Both versions actively prevent external memory fragmentation by scanning for and merging adjacent free blocks back into larger contiguous pools upon process termination.

## How to Compile and Run

### C Version
```bash
gcc "RTOS Sim.c" -o mem_sim
./mem_sim
```

### Java Version
This simulator was built and tested using `Java 17`.

```bash
javac MemorySystem.java
java MemorySystem 
