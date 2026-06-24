#include <stdio.h>
#include <stdlib.h>

struct Block {
    int blockNumber;
    char data[256];
};

int main() {
    FILE *file;
    struct Block block;
    int blockNumber;
    long indexBlock[100] = {0}; // Stores byte offsets within the file

    file = fopen("indexed_file.txt", "wb");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }

    printf("Enter blocks (Enter '0' as block number to exit):\n");
    while (1) {
        printf("Block Number (1-99): ");
        scanf("%d", &block.blockNumber);
        if (block.blockNumber == 0) {
            break;
        }
        printf("Data: ");
        scanf(" %[^\n]", block.data);

        // Record the exact position before writing the block
        indexBlock[block.blockNumber] = ftell(file) + 1; // +1 to differentiate from 0
        fwrite(&block, sizeof(struct Block), 1, file);
    }
    fclose(file);

    file = fopen("indexed_file.txt", "rb");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }

    while (1) {
        printf("\nEnter the block number to read (0 to exit): ");
        scanf("%d", &blockNumber);
        if (blockNumber == 0) {
            break;
        }

        if (indexBlock[blockNumber] == 0) {
            printf("Block not found via index block mapping.\n");
        } else {
            // Seek directly to block position using index
            fseek(file, indexBlock[blockNumber] - 1, SEEK_SET);
            fread(&block, sizeof(struct Block), 1, file);
            printf("Block Number: %d\n", block.blockNumber);
            printf("Data: %s\n", block.data);
        }
    }

    fclose(file);
    remove("indexed_file.txt");
    return 0;
}
