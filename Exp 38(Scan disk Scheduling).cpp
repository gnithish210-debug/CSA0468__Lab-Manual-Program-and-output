#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, head, max_track, seek_time = 0;
    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    int request_queue[n + 1]; // Extra slot to handle boundary limit if needed
    printf("Enter the disk request queue:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &request_queue[i]);
    }
    printf("Enter the initial position of the disk head: ");
    scanf("%d", &head);
    printf("Enter maximum track size limit (e.g., 199): ");
    scanf("%d", &max_track);

    // Sort queue items 
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (request_queue[i] > request_queue[j]) {
                int temp = request_queue[i];
                request_queue[i] = request_queue[j];
                request_queue[j] = temp;
            }
        }
    }

    int index = 0;
    for (int i = 0; i < n; i++) {
        if (head < request_queue[i]) {
            index = i;
            break;
        }
    }

    printf("\nSCAN Head Movement Traversal:\n");
    printf("%d", head);
    
    // Moving towards the larger side first
    for (int i = index; i < n; i++) {
        seek_time += abs(head - request_queue[i]);
        head = request_queue[i];
        printf(" -> %d", head);
    }
    
    // Move to end boundary limit
    seek_time += abs(max_track - head);
    head = max_track;
    printf(" -> %d", head);

    // Turn back and move towards left
    for (int i = index - 1; i >= 0; i--) {
        seek_time += abs(head - request_queue[i]);
        head = request_queue[i];
        printf(" -> %d", head);
    }

    printf("\nTotal Seek Time: %d\n", seek_time);
    printf("Average Seek Time: %.2f\n", (float)seek_time / n);
    return 0;
}
