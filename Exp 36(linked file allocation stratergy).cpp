#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Block {
    char data[256];
    struct Block* next;
};

int main() {
    struct Block* firstBlock = NULL;
    struct Block* lastBlock = NULL;
    int blockCount = 0;
    int blockNumber;
    char data[256];
    char choice;

    printf("Linked Allocation Simulation\n");
    while (1) {
        printf("\nEnter 'W' to write, 'R' to read, or 'Q' to quit: ");
        scanf(" %c", &choice);

        if (choice == 'Q' || choice == 'q') {
            break;
        }
        if (choice == 'W' || choice == 'w') {
            printf("Enter data for the block: ");
            scanf(" %[^\n]", data);
            
            struct Block* newBlock = (struct Block*)malloc(sizeof(struct Block));
            strcpy(newBlock->data, data);
            newBlock->next = NULL;

            if (blockCount == 0) {
                firstBlock = newBlock;
                lastBlock = newBlock;
            } else {
                lastBlock->next = newBlock;
                lastBlock = newBlock;
            }
            blockCount++;
            printf("Block added successfully as index #%d.\n", blockCount);
        } else if (choice == 'R' || choice == 'r') {
            if (blockCount == 0) {
                printf("No blocks allocated yet.\n");
                continue;
            }
            printf("Enter the block number to read (1-%d): ", blockCount);
            scanf("%d", &blockNumber);

            if (blockNumber < 1 || blockNumber > blockCount) {
                printf("Invalid block range.\n");
            } else {
                struct Block* currentBlock = firstBlock;
                for (int i = 1; i < blockNumber; i++) {
                    currentBlock = currentBlock->next;
                }
                printf("Block %d Data: %s\n", blockNumber, currentBlock->data);
            }
        }
    }

    // Free the allocated memory for blocks before exiting
    struct Block* currentBlock = firstBlock;
    while (currentBlock != NULL) {
        struct Block* nextBlock = currentBlock->next;
        free(currentBlock);
        currentBlock = nextBlock;
    }
    return 0;
}
