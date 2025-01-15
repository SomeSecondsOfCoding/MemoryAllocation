#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memory.h"

void print_menu() { // The Menu for you
    printf("\n**Memory Allocation Simulator**\n\n");
    printf("1. Allocate Memory (malloc)\n");
    printf("2. Free Memory (free)\n");
    printf("3. Reallocate Memory (realloc)\n");
    printf("4. Print Memory Pool\n");
    printf("0. Exit\n\n");
    printf("Enter your choice: ");
}

int main() {
    int choice;
    size_t size;    // store the size of the memory to allocate
    void *ptr = NULL;   // store the adress of allocated memory
    int alloc_strategy;     //store the user's choice of allocation strategy

    memory_init();      //initialize the memory pool
    memory_print();     // display the initial state of the memory pool

    while (1) {
        print_menu();

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1: // malloc
                printf("Enter allocation strategy:\n");
                printf("1. First-Fit\n");
                printf("2. Best-Fit\n");
                printf("3. Worst-Fit\n");
                printf("Enter your choice (1-3): ");
                if (scanf("%d", &alloc_strategy) != 1 || alloc_strategy < 1 || alloc_strategy > 3) {
                    printf("Invalid allocation strategy.\n");
                    while (getchar() != '\n');
                    continue;
                }
                printf("Enter size to allocate: ");
                if (scanf("%zu", &size) != 1 || size <= 0) {
                    printf("Invalid size. Please enter a positive number.\n");
                    while (getchar() != '\n');
                    continue;
                }
                ptr = memory_alloc(size, alloc_strategy - 1);
                if (ptr) {
                    printf("Memory allocated at: %p, Size: %zu\n", ptr, size);
                    memory_print();
                } else {
                    printf("Memory allocation failed.\n");
                }
                break;

            case 2: // free
                if (!ptr) {
                    printf("No memory has been allocated yet.\n");
                    break;
                }
                memory_free(ptr);
                ptr = NULL;
                memory_print();
                break;

            case 3: // realloc
                if (!ptr) {
                    printf("No memory has been allocated yet.\n");
                    break;
                }
                printf("Enter new size to reallocate: ");
                if (scanf("%zu", &size) != 1 || size > (SIZE_MAX - sizeof(MemoryBlock))) {
                    printf("Invalid size. Please enter a non-negative number.\n");
                    while (getchar() != '\n');
                    continue;
                }
                void *new_ptr = memory_realloc(ptr, size);
                if (new_ptr) {
                     if (new_ptr != ptr) {
                        printf("Memory reallocated from %p to %p, New Size: %zu\n", ptr, new_ptr, size);
                    } else {
                        printf("Memory reallocated in place, New Size: %zu\n", size);
                    }
                    ptr = new_ptr;
                    memory_print();
                } else {
                    printf("Memory reallocation failed.\n");
                }
                break;

            case 4: // print
                memory_print();
                break;

            case 0: // Exit
                printf("Exiting program.\n");
                return 0;

            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}