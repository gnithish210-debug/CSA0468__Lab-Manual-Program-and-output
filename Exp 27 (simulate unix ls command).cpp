#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() { 
    char fn[50], pat[50], temp[256]; 
    FILE *fp; 
    printf("\nEnter file name: "); 
    scanf("%49s", fn); 
    printf("Enter the pattern to search: "); 
    scanf("%49s", pat); 
    fp = fopen(fn, "r"); 
    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }
    // Safely read line by line until End-Of-File (EOF)
    while (fgets(temp, sizeof(temp), fp) != NULL) { 
        // strstr checks if 'pat' is a substring inside 'temp'
        if (strstr(temp, pat) != NULL) { 
            printf("%s", temp); 
        }
    } 
    fclose(fp); 
    return 0; 
}
