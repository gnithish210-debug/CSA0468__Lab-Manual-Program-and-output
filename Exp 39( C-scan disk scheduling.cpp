#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, head, max_track, seek_time = 0;
    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    int request_queue[n];
    printf("Enter the disk request queue:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &request_queue[i]);
    }
    printf("Enter the initial position of the disk head: ");
    scanf("%d", &head);
    printf("Enter maximum track size limit (e.g., 199): ");
    scanf("%d", &max_track);

    // Sort request queue items
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

    printf("\nC-SCAN Head Movement Sequence:\n");
    printf("%d", head);

    // Traverse outward to the end boundary
    for (int i = index; i < n; i++) {
        seek_time += abs(head - request_queue[i]);
        head = request_queue[i];
        printf(" -> %d", head);
    }

    // Move to max track edge, wrap around to 0
    seek_time += abs(max_track - head);
    seek_time += max_track; // Distance from max_track to 0
    head = 0;
    printf(" -> %d", head);

    // Complete requests from 0 up to the initial split index
    for (int i = 0; i < index; i++) {
        seek_time += abs(head - request_queue[i]);
        head = request_queue[i];
        printf(" -> %d", head);
    }

    printf("\nTotal Seek Time: %d\n", seek_time);
    printf("Average Seek Time: %.2f\n", (float)seek_time / n);
    return 0;
}
