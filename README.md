# Memory Allocation Simulator

## Project Overview

This project demonstrates memory management in the C programming language through a console-based program. It is designed as a student project for the "Procedural Programming for Computer Scientists" module. Users can interactively experiment with various memory management functions, define memory sizes, and observe the effects of different placement algorithms.

## Features

1. **Interactive Console Interface**
   - Users can control program execution via a menu in the console.
   - Selection of different memory management functions is available.

2. **Memory Initialization**
   - The memory pool is initialized to a fixed size of 1024 bytes.

3. **Memory Operations**
   - Dynamic memory allocation (`memory_alloc`).
   - Memory deallocation (`memory_free`).
   - Memory reallocation (`memory_realloc`).

4. **Memory Blocks**
   - Users can define the size of memory blocks to allocate or free.

5. **Placement Algorithms**
   - Implementation and comparison of various memory placement algorithms:
     - **First-Fit:** Allocates the first suitable free block.
     - **Best-Fit:** Allocates the smallest block that fits the request.
     - **Worst-Fit:** Allocates the largest available block.

6. **Memory Visualization**
   - A textual representation of the current memory state, showing allocated and free blocks after each operation.

## Installation

**Build the project:**

`make`

## Usage

**Run the program:**

`./bin/memory`

Follow the on-screen instructions to interact with the memory allocation simulator.

## Target Audience

This program is designed for students and learners in computer science who want to deepen their understanding of memory management and dynamic memory allocation in C through hands-on practice.