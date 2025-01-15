#include "memory.h"
#include <string.h>
#include <stdint.h>

char memory_pool[MEMORY_SIZE]; // the raw memory storage

void memory_init() {
    MemoryBlock *initial_block = (MemoryBlock *)memory_pool;
    initial_block->size = MEMORY_SIZE - sizeof(MemoryBlock);
    initial_block->free = 1;
    initial_block->next = NULL;
}

void *memory_alloc(size_t size, AllocationStrategy strategy) {
    MemoryBlock *current = (MemoryBlock *)memory_pool;
    MemoryBlock *best = NULL;
    size_t best_size = SIZE_MAX;
    MemoryBlock *worst = NULL;
    size_t worst_size = 0;

    while (current) {
        if (current->free && current->size >= size) {
            switch (strategy) {
                case FIRST_FIT:
                    { // Added braces for proper scope
                        size_t remaining = current->size - size;
                        if (remaining >= sizeof(MemoryBlock)) {
                            MemoryBlock *new_block = (MemoryBlock *)((char *)current + sizeof(MemoryBlock) + size);
                            new_block->size = remaining - sizeof(MemoryBlock);
                            new_block->free = 1;
                            new_block->next = current->next;
                            current->next = new_block;
                            current->size = size;
                        }
                        current->free = 0;
                        return (char *)current + sizeof(MemoryBlock);
                    }
                case BEST_FIT:
                    if (current->size < best_size) {
                        best = current;
                        best_size = current->size;
                    }
                    break;
                case WORST_FIT:
                    if (current->size > worst_size) {
                        worst = current;
                        worst_size = current->size;
                    }
                    break;
            }
        }
        current = current->next;
    }

    MemoryBlock *selected = (strategy == BEST_FIT) ? best : ((strategy == WORST_FIT) ? worst : NULL);

    if (!selected) return NULL;

    size_t remaining = selected->size - size;
    if (remaining >= sizeof(MemoryBlock)) {
        MemoryBlock *new_block = (MemoryBlock *)((char *)selected + sizeof(MemoryBlock) + size);
        new_block->size = remaining - sizeof(MemoryBlock);
        new_block->free = 1;
        new_block->next = selected->next;
        selected->next = new_block;
        selected->size = size;
    }

    selected->free = 0;
    return (char *)selected + sizeof(MemoryBlock);
}

void memory_free(void *ptr) {
    if (!ptr) return;
    MemoryBlock *block = (MemoryBlock *)((char *)ptr - sizeof(MemoryBlock));
    block->free = 1;
    memory_coalesce();
}

void memory_coalesce() {
    MemoryBlock *current = (MemoryBlock *)memory_pool;
    while (current && current->next) {
        if (current->free && current->next->free) {
            current->size += sizeof(MemoryBlock) + current->next->size;
            current->next = current->next->next;
        } else {
            current = current->next;
        }
    }
}

void *memory_realloc(void *ptr, size_t new_size) {
    if (!ptr) return memory_alloc(new_size, FIRST_FIT);
    if (new_size == 0) {
        memory_free(ptr);
        return NULL;
    }

    MemoryBlock *old_block = (MemoryBlock *)((char *)ptr - sizeof(MemoryBlock));
    if (old_block->size == new_size) return ptr;

    void *new_ptr = memory_alloc(new_size, FIRST_FIT);
    if (!new_ptr) return NULL;

    memcpy(new_ptr, ptr, (old_block->size < new_size) ? old_block->size : new_size);
    memory_free(ptr);
    return new_ptr;
}

void memory_print() {
    MemoryBlock *current = (MemoryBlock *)memory_pool;
    printf("Memory Pool:\n");
    while (current) {
        printf("Block: %p, Size: %zu, Free: %d\n", (void *)current, current->size, current->free);
        current = current->next;
    }

    current = (MemoryBlock *)memory_pool;
    printf("\nGraphical Representation:\n");
    while (current) {
        printf("[");
        for (size_t i = 0; i < current->size; i++) {
            printf(current->free ? "." : "#");
        }
        printf("]");
        current = current->next;
    }
    printf("\n");
}