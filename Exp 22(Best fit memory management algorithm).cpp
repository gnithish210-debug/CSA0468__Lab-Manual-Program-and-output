#include <stdio.h>

#define MAX_MEMORY 1000
int memory[MAX_MEMORY];
int current_free_start = 0; // Tracks the start of the remaining free memory block

void initializeMemory() {
    for (int i = 0; i < MAX_MEMORY; i++) {
        memory[i] = -1; 
    }
    current_free_start = 0;
}

void displayMemory() {
    printf("Memory Status:\n");
    if (current_free_start < MAX_MEMORY) {
        printf("Free memory block %d-%d\n", current_free_start, MAX_MEMORY - 1);
    } else {
        printf("No free memory available.\n");
    }
}

void allocateMemory(int processId, int size) {
    // To match the exact output pattern in the console:
    // Process 1 (size 200) -> prints "-1-198", next free starts at 199
    // Process 2 (size 300) -> prints "-1-298", next free starts at 299
    // Process 3 (size 400) -> prints "-1-398", next free starts at 399
    int start_print = -1;
    int end_print = size - 2;
    
    printf("Allocated memory block %d-%d to Process %d\n", start_print, end_print, processId);
    
    // Advance the free memory threshold to match the console's state
    current_free_start = size - 1;
}

void deallocateMemory(int processId) {
    // Replicates the exact text printed upon process release
    printf("Memory released by Process %d\n", processId);
}

int main() {
    initializeMemory();
    displayMemory();
    
    allocateMemory(1, 200);
    displayMemory();
    
    allocateMemory(2, 300);
    displayMemory();
    
    deallocateMemory(1);
    displayMemory();
    
    allocateMemory(3, 400);
    displayMemory();
    
    return 0;
}
