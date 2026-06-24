#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <io.h>        // Required for Windows chmod mapping

int main() {
    char filename[] = "file.txt";
    
    // Create the test file if it doesn't exist
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("Error creating file.txt");
        return 1;
    }
    fprintf(fp, "Testing permissions modification code.");
    fclose(fp);

    // Windows equivalent: Set file to Read and Write
    // Note: To make a file Read-Only, you would pass just S_IREAD
    int new_permissions = S_IREAD | S_IWRITE;

    // Windows supports _chmod or chmod via <io.h>
    if (chmod(filename, new_permissions) == 0) { 
        printf("File permissions changed successfully on Windows host.\n");
    } else {
        perror("chmod transformation failed");
        return 1;
    }
    
    return 0;
}
