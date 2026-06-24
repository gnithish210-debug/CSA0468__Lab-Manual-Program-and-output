#include <stdio.h>

#define MAX_FRAMES 3

void printFrames(int frames[], int n) {
    for (int i = 0; i < n; i++) {
        if (frames[i] == -1) {
            printf(" - ");
        } else {
            printf(" %d ", frames[i]);
        }
    }
    printf("\n");
}

int main() {
    int frames[MAX_FRAMES];
    int usageHistory[MAX_FRAMES];
    int pageFaults = 0;
    int referenceString[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int n = sizeof(referenceString) / sizeof(referenceString[0]);

    for (int i = 0; i < MAX_FRAMES; i++) {
        frames[i] = -1;
        usageHistory[i] = 0;
    }

    printf("Reference String: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", referenceString[i]);
    }
    printf("\n\nPage Replacement Order:\n");

    for (int i = 0; i < n; i++) {
        int page = referenceString[i];
        int pageFound = 0;
        int hitIndex = -1;

        for (int j = 0; j < MAX_FRAMES; j++) {
            if (frames[j] == page) {
                pageFound = 1;
                hitIndex = j;
                break;
            }
        }

        if (pageFound) {
            // Update chronological tracking history metrics
            for (int k = 0; k < MAX_FRAMES; k++) {
                if (frames[k] != -1 && k != hitIndex) {
                    usageHistory[k]++;
                }
            }
            usageHistory[hitIndex] = 0; 
        } else {
            printf("Page %d -> ", page);
            int lruPage = 0;
            
            // Check for empty spots first, else discover highest counters
            for (int j = 0; j < MAX_FRAMES; j++) {
                if (frames[j] == -1) {
                    lruPage = j;
                    break;
                }
                if (usageHistory[j] > usageHistory[lruPage]) {
                    lruPage = j;
                }
            }

            int replacedPage = frames[lruPage];
            frames[lruPage] = page;
            
            // Increment history tracking weights
            for (int k = 0; k < MAX_FRAMES; k++) {
                if (frames[k] != -1 && k != lruPage) {
                    usageHistory[k]++;
                }
            }
            usageHistory[lruPage] = 0;

            if (replacedPage != -1) {
                printf("Replace %d with %d: ", replacedPage, page);
            } else {
                printf("Load into an empty frame: ");
            }
            printFrames(frames, MAX_FRAMES);
            pageFaults++;
        }
    }

    printf("\nTotal Page Faults via LRU: %d\n", pageFaults);
    return 0;
}
