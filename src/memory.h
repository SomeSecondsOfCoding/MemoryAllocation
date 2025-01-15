#ifndef MEMORY_H
#define MEMORY_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h> // For size_t
#include <stdint.h> 

#define MEMORY_SIZE 1024       // Size of the memory pool in bytes //a Preprocessor macro

typedef struct MemoryBlock {
    size_t size;             // Size of the memory block in bytes
    int free;                // Flag to indicate if the memory block is free (1) or not (0)
    struct MemoryBlock *next; // Pointer to the next memory block
} MemoryBlock;

typedef enum {
    FIRST_FIT,
    BEST_FIT,
    WORST_FIT
} AllocationStrategy;

// Function prototypes
void memory_init(); // initializes the memory pool
void *memory_alloc(size_t size, AllocationStrategy strategy); // Allocator
void memory_free(void *ptr); //Free
void *memory_realloc(void *ptr, size_t new_size); // Reallocator
void memory_coalesce();
void memory_print();

#endif